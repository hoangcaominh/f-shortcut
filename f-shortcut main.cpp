#include "f-shortcut lib.h"

int main()
{
	about();
	bool _menu = true;
	while(_menu)
    {
        scan_path();

        std::cout << std::endl;
        std::cout << "\"<cancel>\" to cancel any input, except in the menu/submenu and Internet search" << std::endl;
        std::cout << std::endl;
        std::cout << "[1] New path to file/folder" << std::endl;
        std::cout << "[2] Open a file/folder" << std::endl;
        std::cout << "[3] View submenu" << std::endl;
        std::cout << "[4] Rename submenu" << std::endl;
        std::cout << "[5] Delete submenu" << std::endl;
        std::cout << "[6] Search the Internet" << std::endl;
        std::cout << "[7] Clear history" << std::endl;
        std::cout << "[0] Exit" << std::endl;
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
            std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
        }
    }
	return 0;
}
