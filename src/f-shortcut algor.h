#include <string>
#include <fstream>
#define path_number 2000

#include <iostream>
using namespace std;

int current_path_number;

struct dir
{
	string name, path;
}	store[path_number];

int compare_no_capital(string s1, string s2)
{
	string ss1 = "", ss2 = "";

	for (unsigned int i = 0;i < s1.length();i++)
		if (s1[i] >= 65 && s1[i] <= 90)
			ss1 += char(s1[i] + 32);
		else
			ss1 += s1[i];

	for (unsigned int i = 0;i < s2.length();i++)
		if (s2[i] >= 65 && s2[i] <= 90)
			ss2 += char(s2[i] + 32);
		else
			ss2 += s2[i];

	if (ss1.empty())
		return -2;
	else if (ss1 < ss2)
		return -1;
	else if (ss1 > ss2)
		return 1;
    else
        return 0;
}

void align()
{
	for (int i = 0;i < path_number - 1;i++)
	{
		for (int j = i+1;j < path_number;j++)
		{
		   	// if (store[i].name.compare(store[j].name) == 1 || store[i].name.empty())
			if (compare_no_capital(store[i].name, store[j].name) == -2)
		  	{
				dir k = store[i];
	            store[i] = store[j];
	            store[j] = k;
		  	}
		}
	}

	for (int i = 0;i < current_path_number - 1;i++)
	{
		for (int j = i+1;j < current_path_number;j++)
		{
		   	// if (store[i].name.compare(store[j].name) == 1 || store[i].name.empty())
			if (compare_no_capital(store[i].name, store[j].name) == 1)
		  	{
				dir k = store[i];
	            store[i] = store[j];
	            store[j] = k;
		  	}
		}
	}
}

void scan_path()
{
	int i = 0;
	fstream f;
	f.open("data.dat", ios::in);

	while (!f.eof())
	{
		getline(f, store[i].name);
		getline(f, store[i].path);

		if (!store[i].name.empty() && !store[i].name.empty())
			i++;
	}
	f.close();

	current_path_number = i;
	align();
}

void save_path()
{
	fstream f;
	f.open("data.dat", ios::out);
	for (int i = 0;i < path_number;i++)
		if (!store[i].name.empty() && !store[i].path.empty())
		{
			f << store[i].name << endl << store[i].path;
			if (i != path_number - 1)
				f << endl;
		}

	f.close();
}

// specified for search_internet()
#define url_symbol_number 14

struct url_symbol_list
{
    char symbol;
    string id;
} url_symbol[url_symbol_number] = { {' ', "%20"}, {'+', "%2B"}, {'%', "%25"}, {'#', "%23"}, {'&', "%26"}, {'\'', "%27"},
                                    {',', "%2C"}, {'.', "%2E"}, {'/', "%2F"}, {':', "%3A"}, {';', "%3B"}, {'<', "%3C"},
                                    {'=', "&3D"}, {'>', "%3E"} };

string query_convert(string query)
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

string search_url(string engine, string query)
{
    string url = query_convert(query);

    // finalize url
    if (engine == "Google")
        url.insert(0, "www.google.com/search?q=");
    else if (engine == "Bing")
        url.insert(0, "www.bing.com/search?q=");
    else if (engine == "Coc Coc")
        url.insert(0, "www.coccoc.com/search#query=");

    return url;
}
