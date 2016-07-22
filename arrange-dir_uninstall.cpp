// arrange-dir_uninstall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	wstring destination = L"arrange-dir.exe";
	wstring program = L"C:\\Program Files\\ArrangeDir\\arrange-dir.exe";
	if (MoveFile(program.c_str(), destination.c_str())) {
		cout << "Success" << endl;
	}
	else {
		cout << "Fail. Program probably not found where it should be." << endl;
	}
	system("rd /S \"C:\\Program Files\\ArrangeDir\"");
	system("UninstallArrangeDirectoryMenuItem.reg");
	cout << "Program uninstall completed. Press anything to delete the files." << endl;
	system("pause");

	system("del arrange-dir.exe");
	system("del arrange-dir_installer.exe");
	system("del README.txt");
	system("del InstallArrangeDirectoryMenuItem.reg");
	system("del UninstallArrangeDirectoryMenuItem.reg");
	system("start cmd /c del arrange-dir_uninstall.exe");
	system("start cmd /c del arrange-dir_install.exe");

	return 0;
}


