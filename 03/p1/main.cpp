#include <string>
#include <fstream>
#include <iostream>

static int get_points(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 1);
	else
		return (c - 'A' + 27);
}

int main()
{
	int len, pos, total = 0;
	char c;
	std::ifstream input("input.txt");
	std::string line, first, second;

	while(std::getline(input, line))
	{
		len = line.length();
		first = line.substr(0, len / 2);
		second = line.substr(len / 2, len / 2);
		pos = first.find_first_of(second);
		c = first[pos];
		total += get_points(c);
	}
	
	std::cout << "total of the priorities of those item types : " << total << std::endl;
	return (0);
}