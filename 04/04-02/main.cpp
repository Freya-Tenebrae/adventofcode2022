#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>

static std::string::const_iterator get_value_str(std::string *v, std::string::const_iterator it)
{
	while (std::isdigit(*it))
	{
		(*v).push_back(*it);
		it++;
	}
	it++;
	return (it);
}

static void fill_value(std::string line, int (*elf_a)[2], int (*elf_b)[2])
{
	std::string v_1, v_2, v_3, v_4;
	std::string::const_iterator it=line.begin();
	
	it = get_value_str(&v_1, it);
	it = get_value_str(&v_2, it);
	it = get_value_str(&v_3, it);
	get_value_str(&v_4, it);
	(*elf_a)[0] = std::stoi(v_1);
	(*elf_a)[1] = std::stoi(v_2);
	(*elf_b)[0] = std::stoi(v_3);
	(*elf_b)[1] = std::stoi(v_4);
}

static bool overlap_on(int elf_a[2], int elf_b[2])
{
	if ((elf_a[0] >= elf_b[0] && elf_a[0] <= elf_b[1]) || \
		(elf_a[1] >= elf_b[0] && elf_a[1] <= elf_b[1]))
		return (true);
	return (false);
}

int main()
{
	int total = 0, elf_a[2], elf_b[2];
	std::ifstream input("input.txt");
	std::string line, l_1, l_2, l_3;

	while(std::getline(input, line))
	{
		fill_value(line, &elf_a, &elf_b);
		if (overlap_on(elf_a, elf_b) || overlap_on(elf_b, elf_a))
			total++;
	}

	std::cout << "total of assignment pairs that overlap : " << total << std::endl;
	return (0);
}