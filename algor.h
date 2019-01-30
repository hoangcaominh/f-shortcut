#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "json.hpp"

#define DEBUG std::cout << "debug" << std::endl;

using json = nlohmann::json;

std::vector<std::string> tag_list;

json data;

bool string_compare(std::string s1, std::string s2)
{
	std::string ss1 = "", ss2 = "";

	for (size_t i = 0;i < s1.length();i++)
		if (s1[i] >= 65 && s1[i] <= 90)
			ss1 += char(s1[i] + 32);
		else
			ss1 += s1[i];

	for (size_t i = 0;i < s2.length();i++)
		if (s2[i] >= 65 && s2[i] <= 90)
			ss2 += char(s2[i] + 32);
		else
			ss2 += s2[i];

    return ss1 < ss2;
}

// check if a string name is valid
const std::string non_char = "\\/:*?\"<>|";

bool is_string_valid(std::string &s)
{
    return s.find_first_of(non_char) == std::string::npos;
}

void string_fix(std::string &s)
{
    for (size_t i = 0;i < s.length();i++)
        if (s[i] == '\\')
            s[i] = '/';
}

// main functions

// string_compare between 2 path names
void align()
{
    for (size_t i = 0;i < data.size() - 1;i++)
    {
        json &tags = data[i]["Tags"];
        std::sort(tags.begin(), tags.end(), string_compare);
    }

	for (size_t i = 0;i < data.size() - 1;i++)
	{
		for (size_t j = i+1;j < data.size();j++)
		{
		   	// if (data[i]["Name"].get<std::string>().string_compare(data[j].name) == 1 || data[i]["Name"].get<std::string>().empty())
			//DEBUG
			if (!string_compare(data[i]["Name"].get<std::string>(), data[j]["Name"].get<std::string>()))
		  	{
		  	    data[i].swap(data[j]);
		  	}
		}
	}

	std::sort(tag_list.begin(), tag_list.end(), string_compare);
}

void new_file()
{
    std::fstream f("data.json", std::ios::out);
    f << "[]";
    f.close();
}

void scan_path()
{
	std::fstream f("data.json", std::ios::in);

	if (f.fail())
    {
        new_file();
        std::cout << std::endl;
        std::cout << "Data file not found, created a new one." << std::endl;
        return;
    }
    else if (f.peek() == std::ifstream::traits_type::eof())
    {
        new_file();
        std::cout << std::endl;
        std::cout << "Attempted to open an empty data file." << std::endl;
        std::cout << "Deleted invalid file and created a new one." << std::endl;
        return;
    }

	// loading file
	std::cout << std::endl;
	std::cout << "Loading/Updating data file..." << std::endl;

    f >> data;
	if (data.empty())
    {
        data[0]["Name"] = "Notepad";
        data[0]["Path"] = "notepad";
        data[0]["Tags"][0] = "(none)";
    }

	f.close();

	// add tags to tag_list
	tag_list.clear();
	for (size_t i = 0;i < data.size();i++)
    {
        for (size_t j = 0;j < data[i]["Tags"].size();j++)
        {
            std::string tag = data[i]["Tags"][j].get<std::string>();
            if (std::find(tag_list.begin(), tag_list.end(), tag) == tag_list.end())
            {
                tag_list.push_back(tag);
                std::sort(tag_list.begin(), tag_list.end(), string_compare);
            }
        }
    }
    align();

	// finishing loading
	std::cout << "Successully loaded data file." << std::endl;
}

void save_path()
{
	std::fstream f("data.json", std::ios::out);

	f << data;

	f.close();
}

bool already_exist(std::string &s)
{
    for (size_t i = 0;i < data.size();i++)
        if (data[i]["Name"].get<std::string>() == s)
            return true;
    return false;
}

// specified for search_internet()
#define url_symbol_number 14

struct url_symbol_list
{
    char symbol;
    std::string id;
};
const url_symbol_list url_symbol[url_symbol_number] = { {' ', "%20"}, {'+', "%2B"}, {'%', "%25"}, {'#', "%23"},
                                    {'&', "%26"}, {'\'', "%27"}, {',', "%2C"}, {'.', "%2E"}, {'/', "%2F"},
                                    {':', "%3A"}, {';', "%3B"}, {'<', "%3C"}, {'=', "&3D"}, {'>', "%3E"} };

std::string query_convert(std::string query)
{
    unsigned int i = 0;
    while (i < query.length())
    {
        bool found_symbol = false;
        for (int j = 0;j < url_symbol_number;j++)
            if (query[i] == url_symbol[j].symbol)
            {
                query.replace(i, 1, url_symbol[j].id.data());
                i += 3;
                found_symbol = true;
                break;
            }

        if (!found_symbol)
            i++;
    }

    return query;
}

std::string search_url(std::string engine, std::string query)
{
    std::string url = query_convert(query);

    // finalize url
    if (engine == "Google")
        url.insert(0, "www.google.com/search?q=");
    else if (engine == "Bing")
        url.insert(0, "www.bing.com/search?q=");
    else if (engine == "Coc Coc")
        url.insert(0, "www.coccoc.com/search#query=");

    return url;
}
