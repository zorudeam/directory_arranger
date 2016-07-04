#include "stdafx.h"
#include "string"
#include "shlwapi.h"
#include "arrangedir.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

static vector<wstring> extensions;
static vector<wstring> files;
static wstring path;
static DWORD err;

void defPathName() {
	LPWSTR  buf = new wchar_t;
	GetModuleFileName(NULL, buf, MAX_PATH);
	path = (wstring) buf;
	path = path.substr(0, path.find_last_of(L"/\\"));
}

void defFileNames() {
	HANDLE hFind=0;
	WIN32_FIND_DATA data;
	wcout << path << endl;
	//LPCWSTR s = (path + L"\\*.*").c_str();
	wstring s = (path + L"\\*.*");
	hFind = FindFirstFile(s.c_str(), &data);
	cout << "is hFind invalid?" << endl;
	if (hFind != INVALID_HANDLE_VALUE) {
		cout << "No! congratuleishons" << endl;
		//foreach match
		do {
				wstring fn = data.cFileName;
				if (data.cFileName != L"" && data.cFileName != L"." && data.cFileName != L".."
					&& fn.find_last_of(L".") != wstring::npos) {
					wcout << "-" << endl << data.cFileName << endl;
					files.push_back(data.cFileName);
				}
		} while (FindNextFile(hFind, &data));
	}
	else{ //If hFind == invalid handle
		cout << "Fail." << endl;
		err = GetLastError();
	}
	FindClose(hFind);
}

void defExtensions() {
	//foreach file
		for (wstring fileName : files) {
			string fn = string(fileName.begin(), fileName.end());
			if (fileName.find_last_of(L".") != wstring::npos) {
				wstring sub = fileName.substr(fileName.find_last_of(L"."));
				sub = sub.wstring::substr(1);
				extensions.push_back(sub);
			}
			else { cout << "npos" << endl; }
		}
}

BOOL DirectoryExists(LPCWSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void classifyFiles() {
	for (vector<wstring>::size_type i=0; i < files.max_size(); i++) {
		//if each folder doesn't exist, create folder
		try {
			if (extensions.at(i) != L"." && extensions.at(i) != L"..") {
				LPCWSTR folderName = (path + L"\\" + extensions.at(i)).c_str();
				cout << endl;
				//if (!DirectoryExists(folderName)) {
					//monster
					_mkdir(
					(string(path.begin(), path.end()) + "\\" + string(extensions.at(i).begin(), extensions.at(i).end())).c_str()
					);
				//};
				//cout << "Directory boolean: " << DirectoryExists(folderName) << endl;
				LPCWSTR d = (path + L"\\" + extensions.at(i) + L"\\" + files.at(i)).c_str();
				wcout << L"Destination: " << path + L"\\" + extensions.at(i) << endl;
				//move file
				BOOL b = MoveFile((path + L"\\" + extensions.at(i) + L"\\" + files.at(i)).c_str(), d);
				if (b == FALSE) {
					wcout << files.at(i) << L" was NOT moved to " << L" ... " << L"\\" + extensions.at(i) + L"\\" +files.at(i) + L"."<< endl;
					cout<< GetLastError() << endl;
				}
				else {
					wcout << L"Moved " << files.at(i) << L" to " << ( L" ... \\" + extensions.at(i) + L"\\" + files.at(i)) << endl;
				}
				cout << endl;
			}
		}catch (std::out_of_range oor_E) {
			return; //I don't know why does this happen but it seems this is the only solution
		}
	}
}

int main()
{
	try {
		//defPathName();
		path = L"C:\\Users\\Zorudeam\\Desktop\\Carpeta\\G";
		defFileNames();
		defExtensions();
		classifyFiles();
	}
	catch (std::out_of_range ofr) { 
		if(err != 0L){
			cout << "error code: " << err << "\nRefer to https://msdn.microsoft.com/en-us/library/windows/desktop/ms681382(v=vs.85).aspx \n";
			system("pause"); return -2; 
		}
		else {
			cout << "err 0 !" << endl;
			classifyFiles();
		}
	}

	system("pause");
	return 0;
}
