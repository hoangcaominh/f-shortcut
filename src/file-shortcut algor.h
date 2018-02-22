#include <string>
#include <fstream>
#define path_number 2000
using namespace std;

int current_path_number;

struct dir
{
	string name, path;
}	store[path_number];

int compare_no_capital(string s1, string s2)
{
	string ss1 = "", ss2 = "";
	
	for (int i = 0;i < s1.length();i++)
		if (s1[i] >= 65 && s1[i] <= 90)
			ss1 += char(s1[i] + 32);
		else
			ss1 += s1[i];
			
	for (int i = 0;i < s2.length();i++)
		if (s2[i] >= 65 && s2[i] <= 90)
			ss2 += char(s2[i] + 32);
		else
			ss2 += s2[i];
	
	if (ss1.empty())
		return -2;
	else if (ss1 < ss2)
		return -1;
	else if (ss1 == ss2)
		return 0;
	else if (ss1 > ss2)
		return 1;
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
