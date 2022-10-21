#include "../include/LinterRules.h"
#include <iostream>
using namespace std;

vector<string> EnvoirmentBlocks(vector<string>& userFile)
{
	string findBegin = "\\begin";
	string findEnd = "\\end";
	string insertTab = "    ";
	vector<int> beginIndexes;
	vector<int> endIndexes;

	for (int i = 0; i < userFile.size(); i++) {
		if (userFile[i].find(findBegin) != string::npos) {

			int spacesThisLine = CountWordInLine(userFile[i], insertTab);
			int spacesNextLine = CountWordInLine(userFile[i+1], insertTab);

			if (spacesThisLine == spacesNextLine)
				beginIndexes.push_back(i);
		}
	}

	for (int i = 0; i < userFile.size(); i++) {
		if (userFile[i].find(findEnd) != string::npos) {

			int spacesThisLine = CountWordInLine(userFile[i], insertTab);
			int spacesLineBefore = CountWordInLine(userFile[i - 1], insertTab);

			if (spacesThisLine == spacesLineBefore)
				endIndexes.push_back(i);
		}
	}

	for (int i = 0; i < beginIndexes.size(); i++) {
		for (int j = beginIndexes[i] + 1; j < endIndexes[i]; j++) {
			userFile[j].insert(0, insertTab);
		}
	}

	return userFile;
}

int CountWordInLine(string& line, string& word)
{
	int count = 0;
	size_t nPos = line.find(word, 0); // first occurrence
	while (nPos != string::npos)
	{
		count++;
		nPos = line.find(word, nPos + 1);
	}

	return count;
}

vector<string> NewLineSentence(vector<string>& userFile)
{
	for (int i = 0; i < userFile.size(); i++)
	{
		string dot = ". ";
		string tempString = userFile[i];
		string tempSubString;

		vector<int> positions; // Holds all the positions that dot occurs within tempString
		queue<string> sentences;

		//Finds all indexes of dots and spaces combined and saves them in positions
		size_t pos = tempString.find(dot, 0);
		while (pos != string::npos)
		{
			positions.push_back(pos + 2);
			pos = tempString.find(dot, pos + 1);
		}

		// Making a substring out of the indexes found in positions
		for (int j = 0; j < positions.size(); j++) {
			if (j != positions.size() - 1) {
				tempSubString = tempString.substr(positions[j], positions[j + 1] - (positions[j] + 1));
			}
			else if (j == positions.size() - 1) {
				tempSubString = tempString.substr(positions[j], positions.size() - (positions[j] + 1));
			}

			if (tempSubString != "")
			{
				sentences.push(tempSubString);
			}
		}

		if (positions.size() > 0) {
			userFile[i].erase(positions[0]);
		}

		int j = i;
		while (!sentences.empty()) {
			j++;
			userFile.insert(userFile.begin() + j, "\\item " + sentences.front());
			sentences.pop();
		}
	}

	return userFile;
}

vector<string> CommentSpace(vector<string>& userFile) {
	//Finds all % and places a space after if there is none allready
	for (int i = 0; i < userFile.size(); i++)
	{
		for (int j = 0; j < userFile[i].size(); j++) {
			if (userFile[i][j] == '%' && userFile[i][j + 1] != ' ')
			{
				userFile[i].insert(j + 1, " ");
			}
		}
	}
	return userFile;
}

vector<string> BlankLineSection(vector<string>& userFile) {
	string findSection = "\\section";
	vector <int> sectionIndexes;
	int lineCounter = 0;

	//Finds the string \section in the file and saves the lineindex
	for (int i = 0; i < userFile.size(); i++) {
		if (userFile[i].find(findSection) != string::npos) {
			sectionIndexes.push_back(i + lineCounter);
			lineCounter++;
		}
	}

	//Inputs blanklines before section
	for (int i = 0; i < sectionIndexes.size(); i++)
	{
		userFile.insert(userFile.begin() + sectionIndexes[i], "");
	}

	return userFile;
}