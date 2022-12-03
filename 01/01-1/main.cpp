#include <string>
#include <fstream>
#include <iostream>

int main()
{
	int act = 0, max = 0;
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		if (line.compare("") == 0)
		{
			if (act > max)
				max = act;
			act = 0;
		}
		else
			act += std::stoi(line);
	}
	
	std::cout << "total carried by the Elf carrying the most Calories : " << max << std::endl;
	return (0);
}