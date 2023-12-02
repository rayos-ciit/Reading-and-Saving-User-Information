#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//functions//

struct UserData
{
	string FirstName, LastName, Year, Section, Address;
};

string AskUserInput(string question)
{
	cout << question;

	string input;

	getline(cin >> ws, input);
	return input;
}

bool AskUserConfirmation(string question)
{
	string response = AskUserInput(question);
	for (int i = 0; i < response.length(); i++) response[i] = toupper(response[i]);
	if (response == "YES") return true;
	return false;
}

UserData LoadData(string filename)
{
	UserData u;

	ifstream file(filename + ".txt");

	// Load data
	getline(file, u.FirstName);
	getline(file, u.LastName);
	getline(file, u.Address);
	getline(file, u.Year);
	getline(file, u.Section);

	file.close();

	cout << "File Loaded!";

	return u;
}

void SaveData(string filename, UserData u)
{

	ofstream file(filename + ".txt");


	file << u.FirstName + '\n';
	file << u.LastName + '\n';
	file << u.Address + '\n';
	file << u.Year + '\n';
	file << u.Section + '\n';

	file.close();

	cout << "File saved!";
}

void InvalidFunction()
{

	cout << "You have entered an invalid input, please only press the numbers stated." << endl;

}

void MainMenuFunction()
{

	cout << "--------------------------------[Welcome to S1mple Input Machine! press ENTER to PROCEED.]------------------------------" << endl;

}

void EditEnterFunction()
{

	cout << "--------------------------------[Please press [1] if you wish to edit data and [2] if you do not wish to edit data.]----------------------------------------------" << endl;

}

UserData NewUser()
{
	cout << "Make a new user:\n\n";

	UserData user;

	user.FirstName = AskUserInput("First name: ");
	user.LastName = AskUserInput("Last name: ");
	user.Address = AskUserInput("Address: ");
	user.Year = AskUserInput("Year level: ");
	user.Section = AskUserInput("Section: ");

	return user;
}

void DisplayUserData(UserData u)
{
	cout << "\n------------------\n";
	cout << "First Name:" + u.FirstName << endl;
	cout << "Last Name:" + u.LastName << endl;
	cout << "Full Name:" + u.FirstName + " " + u.LastName << endl;
	cout << "Address: " + u.Address + '\n';
	cout << "Year & Section: " + u.Year + " " + u.Section + '\n';
	cout << "\n--------------------" << endl;
}
int main()
{
	//Declarations//
	UserData user;
	system("Color 6");
	int OptionSelect;
	//start//
	MainMenuFunction();
	cin.ignore();
	bool ValidInput = false;
	do
	{
		cout << "[Do you have a previous file?]\n [PRESS 1 for YES]\n [PRESS 2 for NO]" << endl;
		cin >> OptionSelect;
		system("cls");
		switch (OptionSelect)
		{
		case 1:
		{
			ValidInput = true;
			string filename = AskUserInput("[What is your last name?: ]\n");
			ifstream file(filename + ".txt");
			if (file)
			{
				user = LoadData(filename);
			}
			else
			{
				cout << "[User specified does not exist.]" << endl;
				user = NewUser();
			}
			break;
		}
		case 2:
			ValidInput = true;
			user = NewUser();
			DisplayUserData(user);
			break;

		default:
			InvalidFunction();
			cin.ignore();
			break;
		}

	} while (ValidInput == false);

	DisplayUserData(user);


	while (true)
	{
		if (!AskUserConfirmation("[Would you like to edit your data? (Yes/No)]\n")) break;

		cout << "\n------------------\n";
		cout << "Select data to edit\n First name[1], Last name[2], Address[3], Year Level[4], Section[5]\n";

		int input;
		cin >> ws >> input;

		if (!cin)
		{
			cout << "Invalid Input. ";
		}

		switch (input)
		{
		case 1:
			user.FirstName = AskUserInput("First name: ");
			break;

		case 2:
			user.LastName = AskUserInput("Last name: ");
			break;

		case 3:
			user.Address = AskUserInput("Address: ");
			break;

		case 4:
			user.Year = AskUserInput("Year level: ");
			break;

		case 5:
			user.Section = AskUserInput("Section: ");
			break;

		default:
			cout << "Please only type numbers [1]-[5].\n\n";
			continue;
		}

		DisplayUserData(user);
	}

	bool save = AskUserConfirmation("Would you like to save your file? (Yes/No)\n");
	bool previousFileCreated;
	string filename;
	if (save)
	{
		if (!previousFileCreated)
		{
			filename = user.LastName;
		}

		SaveData(filename, user);
	}
}

