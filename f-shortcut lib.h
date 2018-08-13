#include <windows.h>
#include "f-shortcut algor.h"

#define max_name_length 14
#define max_path_length_shown 66

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
    // catch shortcuts overflowing
    if (current_path_number >= path_number)
    {
        cout << "The amount of shortcuts has reached the maximum number, function aborted." << endl;
        cout << "Delete one or more unnecessary paths to continue." << endl;
        return;
    }

	cout << "Type the path of the file/folder:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		string temp_path = str;

		while(true)
        {
            cout << "Type the name of the path:" << endl;
            ask();
            if (cancel())
                return;
            else if (str.length() > max_name_length) // name that longer than 14 chars is invalid
            {
                cout << "Name shouldn't have more than 14 characters. Please rename." << endl;
            }
            else if (already_exist(str))
            {
                cout << "This name has already existed. Please rename or delete the existed one."  << endl;
            }
            else
            {
                store[current_path_number].path = temp_path;
                store[current_path_number].name = str;

                align();

                save_path();
                cout << "Successfully added new path." << endl;

                break;
            }
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

        // if the path length is longer than 66, the latter part is replaced with ...
        if (store[i].path.length() > max_path_length_shown)
            cout << store[i].path.substr(0, max_path_length_shown) << "..." << endl;
        else
            cout << store[i].path << endl;
	}
	cout << "Total: " << current_path_number << "/" << path_number << endl;
}

// 5 //
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

            // start searching
            cout << "Searching for: " << str << "..." << endl;
            string cmd = "start \"\" \"" + search_url(SearchEngine, str) + "\"";
            system(cmd.data());
        }
        else
        {
            cout << "Search engine is either not available or not supported." << endl;
            search_internet();
        }
    }
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

					cout << "Successfully renamed path name." << endl;
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

				while(true)
                {
                    cout << "Type the renamed name:" << endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_name_length)
                    {
                        cout << "Name shouldn't have more than 14 characters. Please rename." << endl;
                    }
                    else if (already_exist(str))
                    {
                        cout << "This name has already existed. Please rename or delete the existed one."  << endl;
                    }
                    else
                    {
                        store[i].name = str;

                        align();
                        save_path();

                        cout << "Successfully renamed path." << endl;
                        return;
                    }
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

				cout << endl << "Successfully deleted path." << endl;
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
	cout << "\"<cancel>\" to cancel any input, except in the menu and Internet search." << endl;
	cout << endl;
	cout << "[1] New path to file/folder" << endl;
	cout << "[2] Open a file/folder" << endl;
	cout << "[3] View a file/folder name and path stored" << endl;
	cout << "[4] View all file/folder names and paths stored" << endl;
	cout << "[5] Search the Internet" << endl;
	cout << "[6] Rename a path" << endl;
	cout << "[7] Rename the name of a path" << endl;
	cout << "[8] Delete a path" << endl;
	cout << "[9] Clear screen and reload file" << endl;
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
		view_all_path();
		menu();
	}
	else if (str == "5")
	{
        search_internet();
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
		scan_path();
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
