#include "TestRules.h"
#include <vector>
#include <string>
#include <iostream>

void TestAllRules() {
	TestEnvoirmentBlocks();
	TestNewLineSentence();
	TestSpaceAfterComment();
	TestBlankLinesSections();
}

void TestEnvoirmentBlocks() {
	vector<string> testVector = { "\\begin", "First test text. Second test text.", "\\end" };

	testVector = EnvoirmentBlocks(testVector);

	if (testVector[1][0] == ' ')
	{
		cout << "Rule 1: Expected!" << endl;
	}
	else {
		cout << "Rule 1: Fail!" << endl;
	}
}

void TestNewLineSentence() {
	vector<string> testVector = { "\\item First test text", "\\item Second test text. Third test text." };

	testVector = NewLineSentence(testVector);

	if (testVector.size() > 2)
	{
		cout << "Rule 2: Expected!" << endl;
	}
	else {
		cout << "Rule 2: Fail!" << endl;
	}
}

void TestSpaceAfterComment() {
	vector<string> testVector = { "%", "\\item Second test text. Third test text." };
	string space = " ";

	testVector = CommentSpace(testVector);

	if (testVector[0].find(space) != string::npos) {
		cout << "Rule 3: Expected!" << endl;
	}
	else {
		cout << "Rule 3: Fail!" << endl;
	}
}

void TestBlankLinesSections() {
	vector<string> testVector = { "\\item First test text", "\\section" , "\\item Second test text", "\\section" };

	testVector = BlankLineSection(testVector);

	if (testVector.size() > 4)
	{
		cout << "Rule 4: Expected!" << endl;
	}
	else {
		cout << "Rule 4: Fail!" << endl;
	}
}