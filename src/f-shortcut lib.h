//#include <iostream>
#include <windows.h>
#include "f-shortcut algor.h"

string str;

bool cancel()
{
	if (str == "<cancel>")
		return true;
	else
		return false;
}

void ask()
{
    // reset buffer
	str = "";
	while (str.empty())
	{
		cout << ">";
		getline(cin, str);
	}
}

// 1 //
void new_path()
{
	cout << "Type the path of the file/folder:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		string temp_path = str;

		cout << "Type the name of the path:" << endl;
		ask();
		if (cancel())
			return;
		else
		{
			store[current_path_number].path = temp_path;
			store[current_path_number].name = str;

			align();

			save_path();
		}
	}
}

// 2 //
void open_path()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;
				cout << "Opening..." << endl;

				string cmd = "start \"\" \"" + store[i].path + "\"";
				system(cmd.data());

				return;
			}

		cout << "Name does not match with any of the stored file name." << endl;
		open_path();
	}
}

// 3 //
void search_a_path()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name: " << store[i].name << endl;
				cout << "Path: " << store[i].path << endl;
				return;
			}

		cout << "Name does not match with any of the stored path name." << endl;
		search_a_path();
	}
}

// 4 //
void search_internet()
{
    cout << "(Supported search engine: Google, Bing, Coc Coc)" << endl;
    cout << "Type the name of the search engine you want to search:" << endl;
    ask();
    if (cancel())
        return;
    else
    {
        if (str == "Google" || str == "Bing" || str == "Coc Coc")
        {
            string SearchEngine = str;

            cout << "Search:" << endl;
            ask();

            string cmd = "start \"\" \"" + search_url(SearchEngine, str) + "\"";
            system(cmd.data());
        }
        else
        {
            cout << "Search engine is not either available or supported." << endl;
            search_internet();
        }
    }
}

// 5 //
void view_all_path()
{
	cout << "Name \t\t\tPath" << endl;
	cout << "----------------------------------------------" << endl;

	for (int i = 0;i < current_path_number;i++)
	{
		cout << "|" << store[i].name;
		if (store[i].name.length() < 8 - 1)
			cout << "\t\t\t";
		else
			cout << "\t\t";

		cout << store[i].path << endl;
	}
	cout << "Total: " << current_path_number << "/" << path_number << endl;
}

// 6 //
void rename_path()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;
				cout << "Type the renamed path:" << endl;
				ask();
				if (cancel())
					return;
				else
				{
					store[i].path = str;

					align();
					save_path();

					cout << "Rename succeeded." << endl;
					return;
				}
			}

		cout << "Name does not match with any of the stored path name." << endl;
		rename_path();
	}
}

// 7 //
void rename_name()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;
				cout << "Type the renamed name:" << endl;
				ask();
				if (cancel())
					return;
				else
				{
					store[i].name = str;

					align();
					save_path();

					cout << "Rename succeeded." << endl;
					return;
				}
			}

		cout << "Name does not match with any of the stored path name." << endl;
		rename_name();
	}
}

// 8 //
void delete_path()
{
	cout << "Type the name of the path you want to delete:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;
				cout << "Deleting...";

				store[i].name = "";
				store[i].path = "";
				current_path_number--;
				align();
				save_path();

				cout << endl << "Delete succeeded." << endl;
				return;
			}

		cout << "Name does not match with any of the stored file name." << endl;
		delete_path();
	}
}

// 9 //
// system("cls");

// old version function //
void about()
{
	system("cls");

	cout << "Hoang Cao Minh product" << endl;
	cout << "This program is intended to link many files and folders." << endl;
	cout << "In other words, shortcut of more than only 1 item." << endl;
}
//////////////////////////

void menu()
{
	scan_path();

	cout << endl;
	cout << "\"<cancel>\" to cancel any input, except in the menu and Internet search" << endl;
	cout << endl;
	cout << "[1] New path to file/folder" << endl;
	cout << "[2] Open a file/folder" << endl;
	cout << "[3] Search a file/folder name and path stored" << endl;
	cout << "[4] Search the Internet" << endl;
	cout << "[5] View all file/folder names and paths stored" << endl;
	cout << "[6] Rename a path" << endl;
	cout << "[7] Rename the name of a path" << endl;
	cout << "[8] Delete a path" << endl;
	cout << "[9] Clear screen" << endl;\
	cout << "[0] Exit" << endl;
	ask();
	if (str == "1")
	{
		new_path();
		menu();
	}
	else if (str == "2")
	{
		open_path();
		menu();
	}
	else if (str == "3")
    {
		search_a_path();
        menu();
    }
	else if (str == "4")
	{
        search_internet();
		menu();
	}
	else if (str == "5")
	{
		view_all_path();
		menu();
	}
	else if (str == "6")
	{
		rename_path();
		menu();
	}
	else if (str == "7")
	{
		rename_name();
		menu();
	}
	else if (str == "8")
	{
		delete_path();
		menu();
	}
	else if (str == "9")
	{
		system("cls");
		menu();
	}
	else if (str == "0")
		return;
	else
	{
		cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
		menu();
	}
}
