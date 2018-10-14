#include <iostream>
#include <windows.h>
#include "f-shortcut algor.h"

#define max_name_length 13
#define max_path_length_shown 43
#define max_cath_length 13

string str;

bool cancel()
{
	if (str == "<cancel>")
    {
        cout << "Action aborted. Returning to main menu..." << endl;
		return true;
    }
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
    if (current_path_number >= max_path_number)
    {
        cout << "The amount of shortcuts has reached the maximum number, action aborted." << endl;
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

		while (true)
        {
            cout << "Type the name of the path:" << endl;
            ask();
            if (cancel())
                return;
            else if (str.length() > max_name_length) // name that longer than 13 chars is invalid
            {
                cout << "Name shouldn't have more than 13 characters. Please rename." << endl;
            }
            else if (already_exist(str))
            {
                cout << "This name has already existed. Please rename or delete the existed one."  << endl;
            }
            else
            {
                // Name is valid. Break the infinite loop
                break;
            }
        }
		string temp_name = str;

		while (true)
        {
            cout << "Type the path category (no category should use (none)):" << endl;
            ask();
            if (cancel())
                return;
            else if (str.length() > max_cath_length) // category that longer than 10 chars is invalid
            {
                cout << "Category name shouldn't have more than 13 characters. Please rename." << endl;
            }
            else
            {
                store[current_path_number].path = temp_path;
                store[current_path_number].name = temp_name;
                store[current_path_number].category = str;

                align();

                save_path();
                cout << "Successfully added a new path." << endl;

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
		for (int i = 0;i < current_path_number;i++)
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

// 3.1 //
void view_a_path()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < current_path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name: " << store[i].name << endl;
				cout << "Path: " << store[i].path << endl;
				cout << "Category: " << store[i].category << endl;
				return;
			}

		cout << "Name does not match with any of the stored path name." << endl;
		view_a_path();
	}
}

// 3.2 //
void view_all_path()
{
	cout << "Name \t\tPath \t\t\t\t\t\tCategory" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	for (int i = 0;i < current_path_number;i++)
	{
		cout << "|" << store[i].name;
		if (store[i].name.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
			cout << "\t\t";
		else
			cout << "\t";

        // if the path length is longer than 66, the latter part is replaced with ...
        if (store[i].path.length() > max_path_length_shown)
            cout << store[i].path.substr(0, max_path_length_shown) << "...\t";
        else
        {
            // (final tab position - first tab position) / 2
            if (store[i].path.length() < 8)
                cout << store[i].path << "\t\t\t\t\t\t";
            else if (store[i].path.length() < 16)
                cout << store[i].path << "\t\t\t\t\t";
            else if (store[i].path.length() < 24)
                cout << store[i].path << "\t\t\t\t";
            else if (store[i].path.length() < 32)
                cout << store[i].path << "\t\t\t";
            else if (store[i].path.length() < 40)
                cout << store[i].path << "\t\t";
            else
                cout << store[i].path << "\t";
        }

        cout << store[i].category << endl;
	}
	cout << "Total: " << current_path_number << "/" << max_path_number << endl;
}

// 3.3 //
void view_a_category()
{
    cout << "Type the category name:" << endl;
    ask();
    if (cancel())
        return;
    else
    {
        int category_item = 0;

        for (int i = 0;i < current_path_number;i++)
            if (store[i].category == str)
            {
                category_item++;
                cout << "|" << store[i].name;


                if (store[i].name.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
                    cout << "\t\t";
                else
                    cout << "\t";
            }

        if (category_item > 0)
            cout << endl << "There are " << category_item << " items in category " << str << endl;
        else
            cout << endl << "There are no items in this category" << endl;
    }
}

// 3.4 //
void view_all_category()
{

    for (int i = 0;i < current_cate_number;i++)
    {
        cout << "|" << category_list[i];

        if (store[i].category.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
            cout << "\t\t";
        else
            cout << "\t";
    }
    cout << endl << "There are a total of " << current_cate_number << " categories" << endl;
}

// 4.1 //
void rename_path()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < current_path_number;i++)
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

					cout << "Successfully renamed name." << endl;
					return;
				}
			}

		cout << "Name does not match with any of the stored path name." << endl;
		rename_path();
	}
}

// 4.2 //
void rename_name()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < current_path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;

				while (true)
                {
                    cout << "Type the renamed name:" << endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_name_length)
                    {
                        cout << "Name shouldn't have more than 13 characters. Please rename." << endl;
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

// 4.3 //
void rename_path_category()
{
	cout << "Type the name of the path:" << endl;
	ask();
	if (cancel())
		return;
	else
    {
		for (int i = 0;i < current_path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;

				while (true)
                {
                    cout << "Type the renamed category for this path:" << endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_cath_length)
                    {
                        cout << "Category name shouldn't have more than 13 characters. Please rename." << endl;
                    }
                    else
                    {
                        store[i].category = str;

                        save_path();

                        cout << "Successfully renamed category for this path." << endl;
                        return;
                    }
                }
			}

		cout << "Name does not match with any of the stored path name." << endl;
		rename_path_category();
    }
}

// 4.4 //
void rename_category()
{
    cout << "Type the existing category:" << endl;
    ask();
	if (cancel())
		return;
	else
    {
        for (int i = 0;i < current_cate_number;i++)
            if (str == category_list[i])
            {
                cout << "Category match." << endl;
                while (true)
                {
                    cout << "Type the renamed category:" << endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_cath_length)
                    {
                        cout << "Category name shouldn't have more than 13 characters. Please rename." << endl;
                    }
                    else
                    {
                        for (int j = 0;j < current_path_number;j++)
                            if (category_list[i] == store[j].category)
                                store[j].category = str;
                        category_list[i] = str;

                        save_path();

                        cout << "Successfully renamed existing category." << endl;
                        return;
                    }
                }
            }

        cout << "Category " << str << " does not exist." << endl;
        rename_category();
    }
}

// 5.1 //
void delete_path()
{
	cout << "Type the name of the path you want to delete:" << endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (int i = 0;i < current_path_number;i++)
			if (str == store[i].name)
			{
				cout << "Name match." << endl;
				cout << "Deleting...";

				store[i].name = "";
				store[i].path = "";
                store[i].category = "";
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

// 5.2 //
void delete_category()
{
    cout << "Type the category you want to delete:" << endl;
    ask();
    if (cancel())
        return;
    else
    {
        for (int i = 0;i < current_cate_number;i++)
            if (str == category_list[i])
            {
                while (true)
                {
                    int category_item = 0;

                    for (int j = 0;j < current_path_number;j++)
                        if (store[j].category == category_list[i])
                            category_item++;

                    cout << "You are going to delete " << category_item << " path(s) in category " << category_list[i] << "." << endl;
                    cout << "Are you sure you want to delete these? (any characters except <cancel> is yes):" << endl;
                    ask();

                    if (cancel())
                        return;
                    else
                    {
                        cout << "Deleting...";
                        for (int j = 0;j < current_path_number;j++)
                            if (store[j].category == category_list[i])
                            {
                                store[j].name = "";
                                store[j].path = "";
                                store[j].category = "";
                                current_path_number--;
                            }

                        align();
                        save_path();

                        cout << endl << "Successfully deleted " << category_item << " path(s)." << endl;
                        return;
                    }
                }
            }

        cout << "Category " << str << " does not exist to be deleted." << endl;
        delete_category();
    }
}

// 6 //
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

void submenu_view()
{
    cout << endl;
    cout << "View submenu:" << endl;
	cout << "[1] View a file/folder name and path stored" << endl;
	cout << "[2] View all file/folder names and paths stored" << endl;
	cout << "[3] View file/folder inside a category" << endl;
	cout << "[4] View all available categories" << endl;
	cout << "[0] Back to main menu" << endl;

	ask();
	if (str == "1")
    {
        view_a_path();
    }
    else if (str == "2")
    {
        view_all_path();
    }
    else if (str == "3")
    {
        view_a_category();
    }
    else if (str == "4")
    {
        view_all_category();
    }
    else if (str == "0")
        return;
    else
    {
		cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
		submenu_view();
    }
}

void submenu_rename()
{
    cout << endl;
    cout << "Rename submenu:" << endl;
	cout << "[1] Rename a path" << endl;
	cout << "[2] Rename the name of a path" << endl;
	cout << "[3] Rename a path's category" << endl;
	cout << "[4] Rename an existing category" << endl;
	cout << "[0] Back to main menu" << endl;

	ask();
	if (str == "1")
    {
        rename_path();
    }
    else if (str == "2")
    {
        rename_name();
    }
    else if (str == "3")
    {
        rename_path_category();
    }
    else if (str == "4")
    {
        rename_category();
    }
    else if (str == "0")
        return;
    else
    {
		cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
		submenu_rename();
    }
}

void submenu_delete()
{
    cout << endl;
    cout << "Delete submenu:" << endl;
	cout << "[1] Delete a path" << endl;
	cout << "[2] Delete a category" << endl;
	cout << "[0] Back to main menu" << endl;

	ask();
	if (str == "1")
    {
        delete_path();
    }
    else if (str == "2")
    {
        delete_category();
    }
    else if (str == "0")
        return;
    else
    {
		cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
		submenu_delete();
    }
}
