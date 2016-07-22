
/* Hello, I am the preprocessors train! */

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include "string"
#include "shlwapi.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "Shlwapi.lib")

using namespace std;

class ArrangeDir {

public:

	vector<wstring> extensions;
	vector<wstring> files;
	wstring path;
	DWORD err;
	int fails = 0;

	ArrangeDir(wstring dir = L"here-warn") {

		try {
			if (dir != L"here-warn" && dir != L"here") {
				path = dir;
			}
			else if (dir == L"here-warn"){
				cout << "Warning, close the program if you don't want to mess with this directory. This could break your computer if running from the wrong directory. Otherwise write start." << endl;
				string s;
				cin >> s;
				if (s == "start") {
					defPathName();
				}
				else exit(0);
			}
			else if (dir == L"here") {
				defPathName();
			}
			defFileNames();
			defExtensions();
			classifyFiles();
			cout << "Fails: " << fails << "\n" << "\n";
		}
		catch (std::out_of_range ofr) {
			if (err != 0L) {
				cout << "error code: " << err << "\nRefer to https://msdn.microsoft.com/en-us/library/windows/desktop/ms681382(v=vs.85).aspx \n";
				system("pause");
			}
			else {
				cout << "err 0 !" << endl;
				classifyFiles();
			}
		}
		
		//process end
		system("pause");

	}

	void defPathName() {
		wchar_t buf[MAX_PATH];
		GetModuleFileNameW(NULL, buf, MAX_PATH);
		path = wstring(buf);
		path = path.substr(0, path.find_last_of(L"/\\"));
	}

	void defFileNames() {
		HANDLE hFind = 0;
		WIN32_FIND_DATA data;
		hFind = FindFirstFile((path + L"\\*.*").c_str(), &data);
		if (hFind != INVALID_HANDLE_VALUE) {
			//foreach match
			do {
				wstring fn = data.cFileName;
				if (data.cFileName != L"" && data.cFileName != L"." && data.cFileName != L".."
					&& fn.find_last_of(L".") != wstring::npos) {
					files.push_back(data.cFileName);
				}
			} while (FindNextFile(hFind, &data));
		}
		else { //If hFind == invalid handle
			cout << "Fail, not a folder." << endl;
			err = GetLastError();
		}
		FindClose(hFind);
	}

	void defExtensions() {
		for (wstring fileName : files) {
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
		for (vector<wstring>::size_type i = 0; i < files.max_size(); i++) {
			//if each folder doesn't exist, create folder
			try {
				if (extensions.at(i).length() != 0) {
					LPCWSTR folderName = (path + L"\\" + extensions.at(i)).c_str();
					cout << endl;
					_mkdir(
						(string(path.begin(), path.end()) + "\\" + string(extensions.at(i).begin(), extensions.at(i).end())).c_str()
					);
					wstring o = path + L"\\" + files.at(i);
					wstring d = path + L"\\" + extensions.at(i) + L"\\" + files.at(i);
					//move file
					wcout << L"Moving " << endl << path + L"\\" + files.at(i) << endl << L" to " << endl << path + L"\\" + extensions.at(i) + L"\\" + files.at(i) << endl;
					BOOL b = MoveFile(o.wstring::c_str(), d.wstring::c_str());
					if (b == FALSE) {
						wcout << "FAIL MOVING " << files.at(i) << endl;
						cout << "Error code: " << GetLastError() << endl;
						fails++;
					}
					else {
						wcout << L"SUCCESS MOVING " << files.at(i) << endl;
					}
					cout << endl;
				}
			}
			catch (std::out_of_range oor_E) {
				return;
			}
		}
	}
};

int main(int argc, char* argv[])
{
	wstring dir = L"here-warn";
	if (argc > 1) {
		string s = "";
		for (int i = 0; i < argc; i++) {
			if (i == 0) continue;
			s = s + argv[i];
			s = s + " ";
		}
		s.pop_back();
		dir = wstring(s.begin(), s.end());
	}
	ArrangeDir process1 (dir);
	return 0;
};
