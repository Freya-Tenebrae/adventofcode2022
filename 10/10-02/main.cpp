#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static void check_cycle(int cycle, int value)
{
	if ((cycle - 1) % 40 >= value - 1 && (cycle - 1) % 40 < value - 1 + 3)
		std::cout << "#";
	else
		std::cout << ".";
	if (cycle % 40 == 0)
		std::cout << std::endl;
}

int main()
{
	int cycle = 0, value = 1;
	std::ifstream input("input.txt");
	std::string line;

	std::cout << "Display :" << std::endl;

	while(std::getline(input, line))
	{
		if (line.compare(0, 4, "noop") == 0)
		{
			cycle++;
			check_cycle(cycle, value);
		}
		else
		{
			cycle ++;
			check_cycle(cycle, value);
			cycle ++;
			check_cycle(cycle, value);
			line.erase(0, 5);
			value += std::stoi(line);
		}
	}
	return (0);
}