#pragma once
#include<vector>
#include<string>
#include<queue>

using namespace std;

vector<string> EnvoirmentBlocks(vector<string>& userFile);

int CountWordInLine(string& line, string& word);

vector<string> NewLineSentence(vector<string>& userFile);

vector<string> CommentSpace(vector<string>& userFile);

vector<string> BlankLineSection(vector<string>& userFile);
