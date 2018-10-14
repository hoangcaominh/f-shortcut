#include <string>
#include <fstream>
#include <algorithm>

#define max_path_number 2000
using namespace std;

int current_path_number;
int current_cate_number;

struct dir
{
	string name, path, category;
}	store[max_path_number];
string category_list[max_path_number];

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

// compare between 2 path names
void align()
{
    /* unnecessary code
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
    */
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

	sort(category_list, category_list + current_cate_number);
}

// compare used for binary search
bool compare(string s1, string s2)
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

    return ss1 < ss2;
}

void scan_path()
{
	unsigned int i = 0;
	unsigned int j = 0;
	fstream f;
	f.open("data.dat", ios::in);

	if (f.fail())
    {
        f.open("data.dat", ios::out);
        f.close();

        cout << endl;
        cout << "File not found, created a new one." << endl;
        return;
    }

	// loading file
	cout << endl;
	cout << "Loading/Updating file..." << endl;
	while (!f.eof())
	{
		getline(f, store[i].name);
		getline(f, store[i].path);
		getline(f, store[i].category);

		if (!store[i].name.empty() && !store[i].path.empty() && !store[i].category.empty())
        {
            // add categories to a separate array
            unsigned int _i;
            for (_i = 0; _i < j; _i++)
                if (category_list[_i] == store[i].category)
                    break;
            if (_i == j)
            {
                category_list[j] = store[i].category;
                j++;
            }

			i++;
        }

        // maximum amount of shortcuts exception
        if (i >= max_path_number)
        {
            cout << "The amount of shortcuts has reached the maximum number, stopped loading." << endl;
            f.close();

            current_path_number = i;
            current_cate_number = j;
            align();
            return;
        }
	}
	f.close();

	current_path_number = i;
    current_cate_number = j;
	align();

	// finishing loading
	cout << "Successully loaded file." << endl;
}

void save_path()
{
	fstream f;
	f.open("data.dat", ios::out);
	for (int i = 0;i < max_path_number;i++)
    {
        f << store[i].name << endl << store[i].path << endl << store[i].category;
        if (i != max_path_number - 1)
            f << endl;
    }

	f.close();
}

bool already_exist(string s)
{
    for (int i = 0;i < current_path_number;i++)
        if (store[i].name == s)
            return true;
    return false;
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
