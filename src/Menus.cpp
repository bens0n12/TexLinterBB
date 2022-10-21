#pragma once
#include "Menus.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <queue>
#include <iterator>

namespace fs = std::filesystem;

using namespace std;

//Menuchoices

void MainMenu() {
	bool doneWithLoop = false;
	int menuChoice;

	vector<string> userFile;

	while (!doneWithLoop)
	{
		if (userFile.size() > 0)
			cout << "Current file: " << userFile[0] << endl;

		menuChoice = PrintMainMenu();
		system("cls");

		switch (menuChoice) {
		case 0:
			//Option to end the program
			doneWithLoop = true;
			break;

		case 1:
			//Option to load a file to the program
			userFile = ReadFile();
			break;

		case 2:
			//Rules
			userFile = EditFile(userFile);
			break;

		case 3:
			if (userFile.size() > 0) {
				SaveFile(userFile);
			}
			else {
				cout << "Please load a file before saving!" << endl;
			}
			break;
		}
	}
}

void CreateInputDir()
{
	if (!fs::is_directory("Input") || !fs::exists("Input")) { // Check if Input folder exists
		fs::create_directory("Input"); // Creats the input folder
	}
}

vector<string> ReadFile() {
	string temp;
	vector<string>userFile;
	vector<string> fileStringsPrint;
	vector<string> fileStringsRead;
	int fileLine;
	string isTexFile = ".tex";

	//Reads all files in the input directory and puts them as strings into the vector fileStringsPrint and fileStringsRead
	std::string path = "./Input";

	cout << "LOAD FILE " << endl << "Put the files that you want to edit in the Input directory" << endl << endl;
	for (const auto& entry : fs::directory_iterator(path)) {
		temp = entry.path().string();

		//Checks if it is a .tex file or not
		if (temp.find(isTexFile) != string::npos) {
			fileStringsRead.push_back(entry.path().string());
			temp = temp.substr(8, temp.length() - 8);
			fileStringsPrint.push_back(temp);
		}
	}

	//Prints all strings in fileStringsPrint to the user and 0 for the user to go back
	for (int i = 0; i < fileStringsPrint.size(); i++) {
		cout << i + 1 << ": " << fileStringsPrint[i] << endl;
	}
	cout << 0 << ": Back" << endl;

	// Asks what line the user wants to load
	cout << "Enter row of the file you want to load:" << endl;

	//If the user enters anything that is not an integer the functions calls itself starts over
	cin >> fileLine;
	system("cls");

	if (!cin)
	{
		cin.clear();
		string ignoreLine; //read the invalid input into it
		getline(cin, ignoreLine); //read the line till next space
		cout << "Please enter the line of the file you want to read with numbers." << endl;
		ReadFile();
	}

	//Checks if the line exists or 0 if the user want to go back
	if (fileLine == 0) {
		return userFile;
	}
	else if (fileLine < 1 || fileLine > fileStringsRead.size()) {
		cout << "That is not a valid line" << endl;
		ReadFile();
	}

	userFile.push_back(fileStringsPrint[fileLine - 1]);

	//Reads the file
	string line;
	ifstream fileToRead(fileStringsRead[fileLine - 1]);
	if (fileToRead.is_open())
	{
		while (getline(fileToRead, line))
		{
			userFile.push_back(line);
		}
	}
	else {
		cout << "Unable to open file!" << endl;
	}
	fileToRead.close();

	return userFile;
}

vector<string> EditFile(vector<string> userFile) {
	bool doneWithRuleLoop = false;
	int menuRuleChoice;

	while (!doneWithRuleLoop) {
		cout << "APPLY RULES" << endl;
		cout << endl;

		//Prints the file
		for (int i = 0; i < userFile.size(); i++)
			cout << userFile[i] << endl;
		cout << endl;

		menuRuleChoice = PrintEditMenu();
		system("cls");

		switch (menuRuleChoice) {
		case 0:
			//Option to go back
			doneWithRuleLoop = true;
			break;

		case 1:
			//Option to make envoirment blocks
			userFile = NewLineSentence(userFile);
			break;

		case 2:
			//Option to make new line after sentence
			userFile = EnvoirmentBlocks(userFile);

			break;

		case 3:
			//Space after % comments
			userFile = CommentSpace(userFile);
			break;

		case 4:
			//Blank lines before section
			userFile = BlankLineSection(userFile);
			break;
		}
	}

	return userFile;
}

void SaveFile(vector <string> userFile) {
	string saveStr = "./Input\\" + userFile[0];

	fstream file;
	file.open(saveStr, ios_base::out);

	for (int i = 1; i < userFile.size(); i++)
	{
		file << userFile[i] << endl;
	}
	file.close();
	cout << "File saved!" << endl;
}