#include <string>
#include <fstream>
#include <iostream>
#include <list>

#define TOP_ELVES 3

int main()
{
	int act = 0, total = 0;
	std::list<int> l;
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		if (line.compare("") == 0)
		{
			l.push_back(act);
			act = 0;
		}
		else
			act += std::stoi(line);
	}
	
	l.sort(std::greater<int>());
	for (int i = 0; i < TOP_ELVES && !l.empty(); l.pop_front())
	{
		total += l.front();
		i++;
	}

	std::cout << "total carried by the " << TOP_ELVES << " elves carrying the most Calories : " << total << std::endl;
	return (0);
}