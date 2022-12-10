#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static void check_cycle(int cycle, int value, std::vector<int> *v)
{
	if (cycle % 40 == 20)
		v->push_back(value * cycle);
}

int main()
{
	int cycle = 0, value = 1, total = 0;
	std::vector<int> v;
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		if (line.compare(0, 4, "noop") == 0)
		{
			cycle++;
			check_cycle(cycle, value, &v);
		}
		else
		{
			cycle ++;
			check_cycle(cycle, value, &v);
			cycle ++;
			check_cycle(cycle, value, &v);
			line.erase(0, 5);
			value += std::stoi(line);
		}
	}

	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		total += *it;

	std::cout << "sum of these six signal strengths : ";
	std::cout << total << std::endl;
	return (0);
}