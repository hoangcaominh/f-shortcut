#include <iostream>
#include <windows.h>
#include "file-shortcut algor.h"

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
	str = "";
	while (str.empty())
	{
		cout << ">";
		getline(cin, str);
	}
}

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
				cout << "Opening...";
				
				string cmd = "start \"\" \"" + store[i].path + "\"";
				system(cmd.data());
				cout << endl << "Open succeeded." << endl;
				return;
			}
			
		cout << "Name does not match with any of the stored file name." << endl;
		open_path();
	}
}

void view_path()
{
	cout << "Name \t\tPath" << endl;
	cout << "----------------------------------------------" << endl;
	
	for (int i = 0;i < current_path_number;i++)
		cout << store[i].name << "\t\t" << store[i].path << endl;
	cout << "Total: " << current_path_number << "/" << path_number << endl;
}

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

void about()
{
	system("cls");
	
	cout << "Hoang Cao Minh product" << endl;
	cout << "This program is intended to link many files and folders." << endl;
	cout << "In other words, shortcut of more than only 1 item." << endl;
}

void menu()
{
	scan_path();
	
	cout << endl;
	cout << "\"<cancel>\" to cancel any input, except in the menu" << endl;
	cout << endl;
	cout << "[1] New path to file/folder" << endl;
	cout << "[2] Open a file/folder" << endl;
	cout << "[3] View all files, folders and paths stored" << endl;
	cout << "[4] Rename a path" << endl;
	cout << "[5] Rename the name of a path" << endl;
	cout << "[6] Delete a path" << endl;
	cout << "[7] Clear screen" << endl;
	cout << "[8] About" << endl;
	cout << "[9] Exit" << endl;
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
		view_path();
		menu();
	}
	else if (str == "4")
	{
		rename_path();
		menu();
	}
	else if (str == "5")
	{
		rename_name();
		menu();
	}
	else if (str == "6")
	{
		delete_path();
		menu();
	}
	else if (str == "7")
	{
		system("cls");
		menu();
	}
	else if (str == "8")
	{
		about();
		menu();
	}
	else if (str == "9")
		return;
	else
	{
		cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
		menu();
	}
}
