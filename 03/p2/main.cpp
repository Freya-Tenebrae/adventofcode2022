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

static int get_pos_char(std::string l_1, std::string l_2, std::string l_3)
{
	std::string l_tmp;
	int pos = 0;

	while (pos != -1)
	{
		pos = l_2.find_first_of(l_3);
		if (pos != -1)
		{
			l_tmp.push_back(l_2[pos]);
			l_2.erase(pos, 1);
		}
	}

	pos = l_1.find_first_of(l_tmp);
	return (pos);
}

int main()
{
	int i = -1, pos = 0, total = 0;
	std::ifstream input("input.txt");
	std::string line, l_1, l_2, l_3;
	char c;

	while(std::getline(input, line))
	{
		i++;
		if (i == 0)
			l_1 = line;
		else if (i == 1)
			l_2 = line;
		else
			l_3 = line;
		if (i == 2)
		{
			pos = get_pos_char(l_1, l_2, l_3);
			c = l_1[pos];
			total += get_points(c);
			i = -1;
		}
	}

	std::cout << "total of the priorities of those item types : " << total << std::endl;
	return (0);
}