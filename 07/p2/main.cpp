#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

#define SPACE_SYSTEM 70000000
#define SPACE_NEEDED 30000000

static void	cd(std::string line, std::string *act_dir)
{
	line.erase(0, 5);
	if (line[0] == '/')
		*act_dir = "/";
	else
	{
		if (line.compare(0, 2, "..") == 0)
		{
			if (*act_dir != "/")
				act_dir->erase(act_dir->find_last_of("/"));
		}
		else
		{
			act_dir->append("/");
			act_dir->append(line);
		}
	}
}

static void	dir(std::string line, std::string *act_dir, \
	std::map<std::string, int> *dir_map)
{
	std::string	dir;

	line.erase(0, 4);
	dir.append(*act_dir, 1);
	dir.append("/");
	dir.append(line);
	dir_map->insert(std::pair<std::string, int>(dir, 0));
}

static void	doc(std::string line, std::string *act_dir, \
	std::map<std::string, int> *doc_map)
{
	std::string	doc;
	int			size_dir;
	std::string::size_type pos;

	size_dir = std::stoi(line, &pos);
	doc.append(*act_dir, 1);
	doc.append("/");
	doc.append(line.substr(pos), 1);
	doc_map->insert(std::pair<std::string, int>(doc, size_dir));
}

static void	size_dir(std::map<std::string, int> *dir_map, \
	std::map<std::string, int> *doc_map)
{
	for (std::map<std::string, int>::iterator it_dir=dir_map->begin(); \
		it_dir!=dir_map->end(); ++it_dir)
	{
		for (std::map<std::string, int>::iterator it_doc=doc_map->begin(); \
			it_doc!=doc_map->end(); ++it_doc)
		{
			if (it_dir->first.compare(0, it_dir->first.length(), \
				it_doc->first, 0, it_dir->first.length()) == 0)
				it_dir->second += it_doc->second;
		}
	}
}

static int	get_size_to_free(std::map<std::string, int> dir_map)
{
	int size_used = 0, size_free, size_to_free;

	for (std::map<std::string, int>::iterator it=dir_map.begin(); \
		it!=dir_map.end(); ++it)
	{
		if (it->first.compare("/") == 0)
			size_used = it->second;
	}
	size_free = (SPACE_SYSTEM - size_used);
	size_to_free = SPACE_NEEDED - size_free;
	return (size_to_free);
}

static int 	get_dir_to_free(std::map<std::string, int> dir_map, int size_to_free)
{
	std::multimap<int, std::string> inv_dir_map;
	for (std::map<std::string, int>::iterator it=dir_map.begin(); \
		it!=dir_map.end(); ++it)
		inv_dir_map.insert(make_pair(it->second, it->first));
	for (std::multimap<int, std::string>::iterator it=inv_dir_map.begin(); \
		it!=inv_dir_map.end(); ++it)
	{
		if (it->first >= size_to_free)
			return (it->first);
	}
	return (0);
}

int main()
{
	int size_to_free = 0;
	std::map<std::string, int> dir_map, doc_map;
	std::ifstream input("input.txt");
	std::string line, act_dir = "/";

	while(std::getline(input, line))
	{
		if (line.compare(0, 4, "$ cd") == 0)
			cd(line, &act_dir);
		else if (line.compare(0, 3, "dir") == 0)
			dir(line, &act_dir, &dir_map);
		else if (line.compare(0, 4, "$ ls") != 0)
			doc(line, &act_dir, &doc_map);
	}

	dir_map.insert(std::pair<std::string, int>("/", 0));
	size_dir(&dir_map, &doc_map);
	size_to_free = get_size_to_free(dir_map);

	std::cout << "the size of the directory to delete is : ";
	std::cout << get_dir_to_free(dir_map, size_to_free) << std::endl;
	return (0);
}