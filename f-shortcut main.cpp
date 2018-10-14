#include "f-shortcut lib.h"

int main()
{
	about();
	bool _menu = true;
	while(_menu)
    {
        scan_path();

        cout << endl;
        cout << "\"<cancel>\" to cancel any input, except in the menu/submenu and Internet search" << endl;
        cout << endl;
        cout << "[1] New path to file/folder" << endl;
        cout << "[2] Open a file/folder" << endl;
        cout << "[3] View an element" << endl;
        cout << "[4] Rename an element" << endl;
        cout << "[5] Delete an element" << endl;
        cout << "[6] Search the Internet" << endl;
        cout << "[7] Clear history" << endl;
        cout << "[0] Exit" << endl;
        ask();
        if (str == "1")
        {
            new_path();
        }
        else if (str == "2")
        {
            open_path();
        }
        else if (str == "3")
        {
            submenu_view();
        }
        else if (str == "4")
        {
            submenu_rename();
        }
        else if (str == "5")
        {
            submenu_delete();
        }
        else if (str == "6")
        {
            search_internet();
        }
        else if (str == "7")
        {
            system("cls");
        }
        else if (str == "0")
            _menu = false;
        else
        {
            cout << "\"" << str << "\"" << "is not recognized as a command." << endl;
        }
    }
	return 0;
}

// Task:
// Create a structure (array, struct, ...) to store sorted categories
