#include <iostream>
#include <windows.h>
#include "f-shortcut algor.h"

#define max_name_length 13
#define max_path_length_shown 43
#define max_tag_length 13

std::string str;

bool cancel()
{
	if (str == "<cancel>")
    {
        std::cout << "Action aborted. Returning to main menu..." << std::endl;
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
		std::cout << ">";
		getline(std::cin, str);

		// fix string
		string_fix(str);
	}
}

// 1 //
void new_path()
{
	std::cout << "Type the path of the file/folder:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		std::string temp_path = str;

		while (true)
        {
            std::cout << "Type the name of the path:" << std::endl;
            ask();
            if (cancel())
                return;
            else if (str.length() > max_name_length) // name that longer than 13 chars is invalid
            {
                std::cout << "Name shouldn't have more than 13 characters. Please rename." << std::endl;
            }
            else if (already_exist(str))
            {
                std::cout << "This name has already existed. Please rename or delete the existed one."  << std::endl;
            }
            else
            {
                // Name is valid. Break the infinite loop
                break;
            }
        }
		std::string temp_name = str;

		while (true)
        {
            std::cout << "Type the path tag (no tag should use (none)):" << std::endl;
            ask();
            if (cancel())
                return;
            else if (str.length() > max_tag_length) // tag that longer than 10 chars is invalid
            {
                std::cout << "Tag name shouldn't have more than 13 characters. Please rename." << std::endl;
            }
            else
            {
                data[data.size()]["Name"] = temp_name;
                data[data.size() - 1]["Path"] = temp_path;
                data[data.size() - 1]["Tags"][0] = str;

                align();

                save_path();
                std::cout << "Successfully added a new path." << std::endl;

                break;
            }
        }
	}
}

// 2 //
void open_path()
{
	std::cout << "Type the name of the path:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name match." << std::endl;
				std::cout << "Opening..." << std::endl;

				std::string cmd = "start \"\" \"" + data[i]["Path"].get<std::string>() + "\"";
				system(cmd.data());

				return;
			}

		std::cout << "Name does not match with any of the saved file name." << std::endl;
		open_path();
	}
}

// 3.1 //
void view_a_path()
{
	std::cout << "Type the name of the path:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name: " << data[i]["Name"] << std::endl;
				std::cout << "Path: " << data[i]["Path"] << std::endl;
				std::cout << "Tag: " << data[i]["Tags"][0] << std::endl;
				return;
			}

		std::cout << "Name does not match with any of the saved path name." << std::endl;
		view_a_path();
	}
}

// 3.2 //
void view_all_path()
{
	std::cout << "Name \t\tPath \t\t\t\t\t\tTag" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	for (size_t i = 0;i < data.size();i++)
	{
		std::string _name = data[i]["Name"].get<std::string>();
		std::cout << "|" << _name;
		if (_name.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
			std::cout << "\t\t";
		else
			std::cout << "\t";

        // if the path length is longer than 66, the latter part is replaced with ...
        std::string _path = data[i]["Path"].get<std::string>();
        if (_path.length() > max_path_length_shown)
            std::cout << _path.substr(0, max_path_length_shown) << "...\t";
        else
        {
            // (final tab position - first tab position) / 2
            if (_path.length() < 8)
                std::cout << _path << "\t\t\t\t\t\t";
            else if (_path.length() < 16)
                std::cout << _path << "\t\t\t\t\t";
            else if (_path.length() < 24)
                std::cout << _path << "\t\t\t\t";
            else if (_path.length() < 32)
                std::cout << _path << "\t\t\t";
            else if (_path.length() < 40)
                std::cout << _path << "\t\t";
            else
                std::cout << _path << "\t";
        }

        std::cout << data[i]["Tags"][0].get<std::string>() << std::endl;
	}
	std::cout << "Total: " << data.size() << std::endl;
}

// 3.3 //
void view_all_tag()
{
    // needs fixing
    for (size_t i = 0;i < tag_list.size();i++)
    {
        std::string tag = tag_list.at(i);
        std::cout << "|" << tag;

        if (tag.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
            std::cout << "\t\t";
        else
            std::cout << "\t";
    }
    std::cout << std::endl << "There are a total of " << tag_list.size() << " tags" << std::endl;
}

// 4.1 //
void rename_path()
{
	std::cout << "Type the name of the path:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name match." << std::endl;
				std::cout << "Type the renamed path:" << std::endl;
				ask();
				if (cancel())
					return;
				else
				{
					data[i]["Path"] = str;

					align();
					save_path();

					std::cout << "Successfully renamed name." << std::endl;
					return;
				}
			}

		std::cout << "Name does not match with any of the saved path name." << std::endl;
		rename_path();
	}
}

// 4.2 //
void rename_name()
{
	std::cout << "Type the name of the path:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name match." << std::endl;

				while (true)
                {
                    std::cout << "Type the renamed name:" << std::endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_name_length)
                    {
                        std::cout << "Name shouldn't have more than 13 characters. Please rename." << std::endl;
                    }
                    else if (already_exist(str))
                    {
                        std::cout << "This name has already existed. Please rename or delete the existed one."  << std::endl;
                    }
                    else
                    {
                        data[i]["Name"] = str;

                        align();
                        save_path();

                        std::cout << "Successfully renamed path." << std::endl;
                        return;
                    }
                }
			}

		std::cout << "Name does not match with any of the saved path name." << std::endl;
		rename_name();
	}
}

// 4.3 //
void rename_path_tag()
{
    // needs fixing
	std::cout << "Type the name of the path:" << std::endl;
	ask();
	if (cancel())
		return;
	else
    {
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name match." << std::endl;

				while (true)
                {
                    std::cout << "Type the renamed tag for this path:" << std::endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_tag_length)
                    {
                        std::cout << "Tag name shouldn't have more than 13 characters. Please rename." << std::endl;
                    }
                    else
                    {
                        data[i]["Tags"][0] = str;

                        save_path();

                        std::cout << "Successfully renamed tag for this path." << std::endl;
                        return;
                    }
                }
			}

		std::cout << "Name does not match with any of the saved path name." << std::endl;
		rename_path_tag();
    }
}

// 4.4 //
void rename_tag()
{
    std::cout << "Type the existing tag:" << std::endl;
    ask();
	if (cancel())
		return;
	else
    {
        for (size_t i = 0;i < tag_list.size();i++)
            if (str == tag_list.at(i))
            {
                std::cout << "Tag match." << std::endl;
                while (true)
                {
                    std::cout << "Type the renamed tag:" << std::endl;
                    ask();

                    if (cancel())
                        return;
                    else if (str.length() > max_tag_length)
                    {
                        std::cout << "Tag name shouldn't have more than 13 characters. Please rename." << std::endl;
                    }
                    else
                    {
                        for (size_t j = 0;j < data.size();j++)
                            if (tag_list.at(i) == data[j]["Tags"][0].get<std::string>())
                                data[j]["Tags"][0] = str;
                        tag_list.at(i) = str;

                        save_path();

                        std::cout << "Successfully renamed existing tag." << std::endl;
                        return;
                    }
                }
            }

        std::cout << "Tag " << str << " does not exist." << std::endl;
        rename_tag();
    }
}

// 5.1 //
void delete_path()
{
	std::cout << "Type the name of the path you want to delete:" << std::endl;
	ask();
	if (cancel())
		return;
	else
	{
		for (size_t i = 0;i < data.size();i++)
			if (str == data[i]["Name"].get<std::string>())
			{
				std::cout << "Name match." << std::endl;
				std::cout << "Deleting...";

				data.erase(i);

				align();
				save_path();

				std::cout << std::endl << "Successfully deleted path." << std::endl;
				return;
			}

		std::cout << "Name does not match with any of the saved file name." << std::endl;
		delete_path();
	}
}

// 5.2 //
void delete_tag()
{
    std::cout << "Type the tag you want to delete:" << std::endl;
    ask();
    if (cancel())
        return;
    else
    {
        for (size_t i = 0;i < tag_list.size();i++)
            if (str == tag_list[i])
            {
                while (true)
                {
                    std::cout << "Deleting...";

                    for (size_t j = 0;j < data.size();j++)
                        if (data[j]["Tags"][0].get<std::string>() == tag_list[i])
                            data[j]["Tags"][0] = "(none)";

                    align();
                    save_path();

                    std::cout << std::endl << "Successfully deleted tag" << std::endl;
                    return;
                }
            }

        std::cout << "Tag " << str << " does not exist to be deleted." << std::endl;
        delete_tag();
    }
}

// 6 //
void search_internet()
{
    std::cout << "(Supported search engine: Google, Bing, Coc Coc)" << std::endl;
    std::cout << "Type the name of the search engine you want to search:" << std::endl;
    ask();
    if (cancel())
        return;
    else
    {
        if (str == "Google" || str == "Bing" || str == "Coc Coc")
        {
            std::string SearchEngine = str;

            std::cout << "Search:" << std::endl;
            ask();

            std::string cmd = "start \"\" \"" + search_url(SearchEngine, str) + "\"";
            system(cmd.data());
        }
        else
        {
            std::cout << "Search engine is not either available or supported." << std::endl;
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

	std::cout << "Hoang Cao Minh product" << std::endl;
	std::cout << "This program is intended to link many files and folders." << std::endl;
	std::cout << "In other words, shortcut of more than only 1 item." << std::endl;
}
//////////////////////////

void submenu_view()
{
    std::cout << std::endl;
    std::cout << "View submenu:" << std::endl;
	std::cout << "[1] View an element's properties" << std::endl;
	std::cout << "[2] View all elements" << std::endl;
	std::cout << "[3] View all existing tags" << std::endl;
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
	std::cout << "[2] Delete an existing tag" << std::endl;
	std::cout << "[0] Back to main menu" << std::endl;

	ask();
	if (str == "1")
    {
        delete_path();
    }
    else if (str == "2")
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
