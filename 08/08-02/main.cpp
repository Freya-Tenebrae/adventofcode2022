#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static int score_row(std::vector<std::vector<int>> map, \
	int i, int j, int x, int n)
{
	int value = map[i][j], z = 1;

	for (z = 1; z*n+j < x && z*n+j >= 0; z++)
		if (value <= map[i][z*n+j])
		{
			z++;
			break ;
		}
	z--;
	return (z);
}
static int score_col(std::vector<std::vector<int>> map, \
	int i, int j, int y, int n)
{
	int value = map[i][j], z = 1;

	for (z = 1; z*n+i < y && z*n+i >= 0; z++)
		if (value <= map[z*n+i][j])
		{
			z++;
			break ;
		}
	z--;
	return (z);
}

static int score_for_pos(std::vector<std::vector<int>> map, \
	int i, int j, int x, int y)
{
	int score = 1;

	if (i == y - 1 || i == 0 || j == x - 1 || j == 0)
		return (0);
	score *= score_row(map, i, j, x, -1);
	score *= score_row(map, i, j, x, 1);
	score *= score_col(map, i, j, y, -1);
	score *= score_col(map, i, j, y, 1);
	return (score);
}

int main()
{
	std::vector<std::vector<int>> map;
	int x, y = 0, score = 0, score_max = 0, x_max, y_max;
	std::ifstream input("input.txt");
	std::string line;

	while(std::getline(input, line))
	{
		std::vector<int> row;

		if (y == 0)
			x = line.length();
		y++;
		for (std::string::iterator it=line.begin(); it!=line.end(); ++it)
			row.push_back(*it - '0');
		map.push_back(row);
	}

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			score = score_for_pos(map, i, j, x, y);
			if (score > score_max)
			{
				x_max = j;
				y_max = i;
				score_max = score;
			}
		}
	}

	std::cout << "the highest scenic score possible is : ";
	std::cout << score_max << " at [" ;
	std::cout << x_max << ", " << y_max << "]" << std::endl;
	return (0);
}