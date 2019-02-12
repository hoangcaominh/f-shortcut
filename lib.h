#include <iostream>
#include <windows.h>
#include "algor.h"

#define max_name_length 13
#define max_path_length_shown 66
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

// 1.1 //
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
            else if (!is_string_valid(str))
            {
                std::cout << "A name can't contain any of the following characters: \\ / : * ? \" < > |" << std::endl;
            }
            else
            {
                // Name is valid. Break the infinite loop
                break;
            }
        }

        data[data.size()]["Name"] = str;
        data[data.size() - 1]["Path"] = temp_path;

        align();

        save_path();
        std::cout << "Successfully added a new path." << std::endl;
        std::cout << "You can add tags to this path with the Add new tag function." << std::endl;
	}
}

// 1.2 //
void new_tag()
{
    while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::string temp_name = str;
                    std::cout << "Name match." << std::endl;
                    std::cout << "Add a new tag (stop adding with <end> tag):" << std::endl;
                    while (true)
                    {
                        ask();
                        if (cancel())
                            return;
                        else if (str == "<end>")
                        {
                            std::cout << "Stopped adding. Returning to main menu..." << std::endl;
                            return;
                        }
                        else if (!is_string_valid(str))
                        {
                            std::cout << "A tag can't contain any of the following characters: \\ / : * ? \" < > |" << std::endl;
                        }
                        else
                        {
                            json &tags = data[i]["Tags"];
                            json::iterator found = std::find(tags.begin(), tags.end(), str);
                            if (found == tags.end())
                            {
                                if (tags.size() == 1 && tags[0] == "(none)")
                                {
                                    // Remove tag (none) for new tag
                                    tags.erase(0);
                                }
                                tags[tags.size()] = str;

                                align();
                                save_path();

                                std::cout << "Added tag \"" << str << "\" to " << temp_name << std::endl;
                            }
                            else
                            {
                                std::cout << "This tag is already added." << std::endl;
                            }
                        }
                    }
                }

            std::cout << "Name does not match with any of the saved file name." << std::endl;
        }
    }
}

// 2 //
void open_path()
{
	while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name match." << std::endl;
                    std::cout << "Opening..." << std::endl;

                    std::string cmd = "start \"\" \"" + data[i]["Path"].get<std::string>() + "\"";
                    system(cmd.data());

                    return;
                }

            std::cout << "Name does not match with any of the saved file name." << std::endl;
        }
    }
}

// 3.1 //
void view_a_path()
{
    while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name: " << data[i]["Name"].get<std::string>() << std::endl;
                    std::cout << "Path: " << data[i]["Path"].get<std::string>() << std::endl;
                    json &tags = data[i]["Tags"];
                    std::cout << "Tags: ";
                    for (size_t j = 0;j < tags.size();j++)
                    {
                        std::cout << tags[j].get<std::string>();
                        if (j != tags.size() - 1)
                            std::cout << ", ";
                    }
                    std::cout << std::endl;
                    return;
                }

            std::cout << "Name does not match with any of the saved path name." << std::endl;
        }
    }
}

// 3.2 //
void view_all_path()
{
	std::cout << "Name \t\tPath" << std::endl;
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;

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
            std::cout << _path.substr(0, max_path_length_shown) << "..." << std::endl;
        else
        {
            std::cout << _path << std::endl;
            /*
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
            */
        }
	}
	std::cout << "Total: " << data.size() << " items" << std::endl;
}

// 3.3
void view_tag_path()
{
    while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < tag_list.size();i++)
                if (str == tag_list.at(i))
                {
                    size_t items = 0;
                    for (size_t j = 0;j < data.size();j++)
                    {
                        json temp = data[j];
                        if (std::find(temp["Tags"].begin(), temp["Tags"].end(), str) != temp["Tags"].end())
                        {
                            items++;
                            std::string name = temp["Name"].get<std::string>();
                            std::cout << "|" << name;

                            if (name.length() < 8 - 1) // (final tab position - first tab position) / 2 - 1 because -1 is |
                                std::cout << "\t\t";
                            else
                                std::cout << "\t";
                        }
                    }
                    std::cout << std::endl << "Total: " << items << " items with tag " << str << "." << std::endl;
                    return;
                }

            std::cout << "Tag does not match with any of the path's tags." << std::endl;
        }
    }
}

// 3.4 //
void view_all_tag()
{
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
void modify_path()
{
    while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name match." << std::endl;
                    std::cout << "Type the modified path:" << std::endl;
                    ask();
                    if (cancel())
                        return;
                    else
                    {
                        data[i]["Path"] = str;

                        align();
                        save_path();

                        std::cout << "Successfully modified name." << std::endl;
                        return;
                    }
                }

            std::cout << "Name does not match with any of the saved path name." << std::endl;
        }
    }
}

// 4.2 //
void modify_name()
{
	while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name match." << std::endl;

                    while (true)
                    {
                        std::cout << "Type the modified name:" << std::endl;
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
                        else if (!is_string_valid(str))
                        {
                            std::cout << "A name can't contain any of the following characters: \\ / : * ? \" < > |" << std::endl;
                        }
                        else
                        {
                            data[i]["Name"] = str;

                            align();
                            save_path();

                            std::cout << "Successfully modified path." << std::endl;
                            return;
                        }
                    }
                }

            std::cout << "Name does not match with any of the saved path name." << std::endl;
        }
    }
}

// 4.3 //
void modify_path_tag()
{
	while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name match." << std::endl;

                    // check if path has no tags
                    json &tags = data[i]["Tags"];
                    if (tags.size() == 1 && tags[0] == "(none)")
                    {
                        std::cout << "This path has no tags. Returning to main menu..." << std::endl;
                        return;
                    }

                    while (true)
                    {
                        std::cout << "Type the tag you want to modify:" << std::endl;
                        ask();
                        if (cancel())
                            return;
                        else if (str == "(none)")
                        {
                            std::cout << "You cannot modify tag (none)." << std::endl;
                        }
                        else if (!is_string_valid(str))
                        {
                            std::cout << "A tag can't contain any of the following characters: \\ / : * ? \" < > |" << std::endl;
                        }
                        else
                        {
                            json::iterator found = std::find(tags.begin(), tags.end(), str);
                            if (found != tags.end())
                            {
                                std::cout << "Tag match." << std::endl;
                                std::cout << "Type the modified tag for this path:" << std::endl;
                                ask();
                                if (cancel())
                                    return;
                                else if (str.length() > max_tag_length)
                                {
                                    std::cout << "Tag name shouldn't have more than 13 characters. Please rename." << std::endl;
                                }
                                else if (std::find(tags.begin(), tags.end(), str) != tags.end())
                                {
                                    std::cout << "This tag is already added. Please rename." << std::endl;
                                }
                                else
                                {
                                    *found = str;

                                    save_path();

                                    std::cout << "Successfully modified tag." << std::endl;
                                    return;
                                }
                            }
                            else
                            {
                                std::cout << "Tag does not match with any of the path's tags." << std::endl;
                            }
                        }
                    }
                }

            std::cout << "Name does not match with any of the saved path name." << std::endl;
        }
    }
}

// 4.4 //
void modify_tag()
{
    while (true)
    {
        std::cout << "Type the existing tag:" << std::endl;
        ask();
        if (cancel())
            return;
        else if (str == "(none)")
        {
            std::cout << "You cannot modify tag (none)." << std::endl;
        }
        else
        {
            for (size_t i = 0;i < tag_list.size();i++)
                if (str == tag_list.at(i))
                {
                    std::cout << "Tag match." << std::endl;
                    while (true)
                    {
                        std::cout << "Type the modified tag:" << std::endl;
                        ask();

                        if (cancel())
                            return;
                        else if (str.length() > max_tag_length)
                        {
                            std::cout << "Tag name shouldn't have more than 13 characters. Please rename." << std::endl;
                        }
                        else if (std::find(tag_list.begin(), tag_list.end(), str) != tag_list.end())
                        {
                            std::cout << "This tag already exists. Please rename." << std::endl;
                        }
                        else if (!is_string_valid(str))
                        {
                            std::cout << "A tag can't contain any of the following characters: \\ / : * ? \" < > |" << std::endl;
                        }
                        else
                        {
                            for (size_t j = 0;j < data.size();j++)
                            {
                                json &tags = data[j]["Tags"];
                                json::iterator found = std::find(tags.begin(), tags.end(), tag_list.at(i));
                                if (found != tags.end())
                                {
                                    *found = str;
                                }
                            }
                            tag_list.at(i) = str;

                            save_path();

                            std::cout << "Successfully modified existing tag." << std::endl;
                            return;
                        }
                    }
                }

            std::cout << "Tag " << str << " does not exist." << std::endl;
        }
    }
}

// 5.1 //
void delete_path()
{
	while (true)
    {
        std::cout << "Type the name of the path you want to delete:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
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
        }
    }
}

// 5.2 //
void delete_path_tag()
{
	while (true)
    {
        std::cout << "Type the name of the path:" << std::endl;
        ask();
        if (cancel())
            return;
        else
        {
            for (size_t i = 0;i < data.size();i++)
                if (str == data[i]["Name"])
                {
                    std::cout << "Name match." << std::endl;

                    // check if path has no tags
                    json &tags = data[i]["Tags"];
                    if (tags.size() == 1 && tags[0] == "(none)")
                    {
                        std::cout << "This path has no tags. Returning to main menu..." << std::endl;
                        return;
                    }

                    while (true)
                    {
                        std::cout << "Type the tag you want to delete:" << std::endl;
                        ask();
                        if (cancel())
                            return;
                        else if (str == "(none)")
                        {
                            std::cout << "You cannot delete tag (none)." << std::endl;
                        }
                        else
                        {
                            json::iterator found = std::find(tags.begin(), tags.end(), str);
                            if (found != tags.end())
                            {
                                std::cout << "Tag match." << std::endl;
                                std::cout << "Deleting...";

                                tags.erase(found);
                                if (tags.size() == 0)
                                {
                                    tags[0] = "(none)";
                                }

                                align();
                                save_path();

                                std::cout << std::endl << "Successfully deleted tag." << std::endl;
                                return;
                            }
                            else
                            {
                                std::cout << "Tag does not match with any of the path's tags." << std::endl;
                            }
                        }
                    }
                }

            std::cout << "Name does not match with any of the saved path name." << std::endl;
        }
    }
}

// 5.3 //
void delete_tag()
{
    while (true)
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
                        {
                            json &tags = data[j]["Tags"];
                            json::iterator found = std::find(tags.begin(), tags.end(), str);
                            if (found != tags.end())
                            {
                                tags.erase(found);
                                if (tags.empty())
                                {
                                    tags[0] = "(none)";
                                }
                            }
                        }

                        align();
                        save_path();

                        std::cout << std::endl << "Successfully deleted tag" << std::endl;
                        return;
                    }
                }

            std::cout << "Tag " << str << " does not exist to be deleted." << std::endl;
        }
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
        }
    }
}
