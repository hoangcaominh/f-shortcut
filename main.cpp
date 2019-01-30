#include "lib.h"

void about()
{
    std::cout << std::endl;
	std::cout << "Hoang Cao Minh product" << std::endl;
	std::cout << "This program is written to store file and folder paths and execute them." << std::endl;
	std::cout << "This even works for URLs so you can go to the page you want without opening a browser first." << std::endl;
	std::cout << "This program is similar to a shortcut, and it works as many shortcuts." << std::endl;
	std::cout << "You can add, view, rename and delete items that store name, path and tags." << std::endl;
	std::cout << "Paths with tags can help you search efficiently." << std::endl;
	std::cout << "Additionally, you can search the Internet directly from this program as well." << std::endl;
}

void submenu_new()
{
    std::cout << std::endl;
    std::cout << "New submenu:" << std::endl;
    std::cout << "[1] Add new element" << std::endl;
    std::cout << "[2] Add new tag" << std::endl;
    std::cout << "[0] Back to main menu" << std::endl;

    ask();
    if (str == "1")
    {
        new_path();
    }
    else if (str == "2")
    {
        new_tag();
    }
    else if (str == "0")
        return;
    else
    {
		std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
		submenu_new();
    }
}

void submenu_view()
{
    std::cout << std::endl;
    std::cout << "View submenu:" << std::endl;
	std::cout << "[1] View an element's properties" << std::endl;
	std::cout << "[2] View all elements" << std::endl;
	std::cout << "[3] View all elements with tag search" << std::endl;
	std::cout << "[4] View all existing tags" << std::endl;
	std::cout << "[0] Back to main menu" << std::endl;

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
        view_tag_path();
    }
    else if (str == "4")
    {
        view_all_tag();
    }
    else if (str == "0")
        return;
    else
    {
		std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
		submenu_view();
    }
}

void submenu_rename()
{
    std::cout << std::endl;
    std::cout << "Rename submenu:" << std::endl;
	std::cout << "[1] Rename an element's name" << std::endl;
	std::cout << "[2] Rename an element's path" << std::endl;
	std::cout << "[3] Rename an element's tag" << std::endl;
	std::cout << "[4] Rename an existing tag" << std::endl;
	std::cout << "[0] Back to main menu" << std::endl;

	ask();
    if (str == "1")
    {
        rename_name();
    }
	else if (str == "2")
    {
        rename_path();
    }
    else if (str == "3")
    {
        rename_path_tag();
    }
    else if (str == "4")
    {
        rename_tag();
    }
    else if (str == "0")
        return;
    else
    {
		std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
		submenu_rename();
    }
}

void submenu_delete()
{
    std::cout << std::endl;
    std::cout << "Delete submenu:" << std::endl;
	std::cout << "[1] Delete an existing element" << std::endl;
	std::cout << "[2] Delete an element's tag" << std::endl;
	std::cout << "[3] Delete an existing tag" << std::endl;
	std::cout << "[0] Back to main menu" << std::endl;

	ask();
	if (str == "1")
    {
        delete_path();
    }
    else if (str == "2")
    {
        delete_path_tag();
    }
    else if (str == "3")
    {
        delete_tag();
    }
    else if (str == "0")
        return;
    else
    {
		std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
		submenu_delete();
    }
}

int main(int argc, char* argv[])
{
	about();

	while(true)
    {
        scan_path();

        std::cout << std::endl;
        std::cout << "\"<cancel>\" to cancel any input, except in the menu/submenu and Internet search" << std::endl;
        std::cout << std::endl;
        std::cout << "[1] New submenu" << std::endl;
        std::cout << "[2] Open" << std::endl;
        std::cout << "[3] View submenu" << std::endl;
        std::cout << "[4] Rename submenu" << std::endl;
        std::cout << "[5] Delete submenu" << std::endl;
        std::cout << "[6] Search the Internet" << std::endl;
        std::cout << "[7] Clear history" << std::endl;
        std::cout << "[8] About" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        ask();
        if (str == "1")
        {
            submenu_new();
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
        else if (str == "8")
        {
            about();
        }
        else if (str == "0")
            break;
        else
        {
            std::cout << "\"" << str << "\"" << "is not recognized as a command." << std::endl;
        }
    }
	return 0;
}
