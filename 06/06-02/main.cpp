#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static bool is_marker(std::vector<char> v)
{
	for (std::vector<char>::const_iterator it=v.begin(); it!=v.end(); ++it)
	{
		std::vector<char>::const_iterator it_bis=it;
		for (++it_bis; it_bis!=v.end(); ++it_bis)
		{
			if (*it == *it_bis || *it == '\0' || *it_bis == '\0')
				return (false);
		}
	}
	return (true);
}

int main()
{
	int n_char = 0;
	std::vector<char> v(14, '\0');
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		for (std::string::const_iterator it=line.begin(); it!=line.end(); ++it)
		{
			n_char++;
			v.erase(v.begin());
			v.push_back(*it);
			if (is_marker(v) == true)
			{
				break ;
				break ;
			}
		}
	}

	std::cout << "number of characters need to be processed before the first start-of-message marker is detected : ";
	std::cout << n_char << std::endl;
	return (0);
}