#include "GUI.h"

int PrintMainMenu() {
	int menuChoice;

	cout << "What do you want to do? " << endl;
	cout << "1. Load document " << endl;
	cout << "2. Edit document  " << endl;
	cout << "3. Save document " << endl;
	cout << "0. Quit " << endl;

	cin >> menuChoice;
	if (!cin)
	{
		cin.clear();
		string ignoreLine; //read the invalid input into it
		getline(cin, ignoreLine); //read the line till next space
		system("cls");
		cout << "Please enter what menuchoice you want with numbers." << endl;
		PrintMainMenu();
	}

	return menuChoice;
}

int PrintEditMenu()
{
	int menuRuleChoice;

	cout << "Select rule " << endl;
	cout << "1. New line for sentences " << endl;
	cout << "2. Environment blocks " << endl;
	cout << "3. Space after % comment " << endl;
	cout << "4. Blank lines for sections" << endl;
	cout << "0. Back " << endl;

	cin >> menuRuleChoice;
	if (!cin)
	{
		cin.clear();
		string ignoreLine; //read the invalid input into it
		getline(cin, ignoreLine); //read the line till next space
		system("cls");
		cout << "Please enter what rule to apply with numbers." << endl;
		PrintEditMenu();
	}

	return menuRuleChoice;
}