#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "GUI.h"
#include "../include/LinterRules.h"

namespace fs = std::filesystem;

using namespace std;

void MainMenu();

void CreateInputDir();

vector<string> ReadFile();

vector<string> EditFile(vector<string> userFile);

void SaveFile(vector<string> userFile);