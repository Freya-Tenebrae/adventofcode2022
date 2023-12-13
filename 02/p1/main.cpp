#include <string>
#include <fstream>
#include <iostream>

static int	point_choice(char you)
{
	if (you == 'A') // rock == 1
		return (1);
	if (you == 'B') // paper == 2
		return (2);
	if (you == 'C') // scissors == 3
		return (3);
	return (0); // error
}

static int	point_result(char opp, char you)
{
	if ((opp == 'A' && you == 'C') || \
		(opp == 'B' && you == 'A') || \
		(opp == 'C' && you == 'B')) // lose == 0
		return (0);
	else if (opp == you) // draw == 3
		return (3);
	else
		return (6);
}

int main()
{
	int total = 0;
	char opp, you;
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		opp = line[0];
		you = line[2] - 'X' + 'A';
		total += point_choice(you) + point_result(opp, you);
	}
	
	std::cout << "total point you get if everything goes exactly as planned : " << total << std::endl;
	return (0);
}