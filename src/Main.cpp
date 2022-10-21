#include <iostream>
#include "Menus.h"
#include "GUI.h"
#include "../include/LinterRules.h"
#include "../tests/TestRules.h"

int main()
{
	TestAllRules();

	CreateInputDir();

	MainMenu();

	return 0;
}