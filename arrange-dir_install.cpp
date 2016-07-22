// arrange-dir_install.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	system("mkdir \"C:\\Program Files\\ArrangeDir\"");
	wstring program = L"arrange-dir.exe";
	wstring destination = L"C:\\Program Files\\ArrangeDir\\arrange-dir.exe";
	if (MoveFile(program.c_str(), destination.c_str())) {
		cout << "Success" << endl;
	}
	else {
		cout << "Fail. Cannot find arrange-dir.exe in the current directory." << endl;
	}
	system("InstallArrangeDirectoryMenuItem.reg");
	system("pause");
    return 0;
}

