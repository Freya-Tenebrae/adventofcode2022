#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static bool is_visible_row(std::vector<std::vector<int>> map, \
	int i, int j, int x, int n)
{
	int value = map[i][j];

	for (int z = 1; z*n+j < x && z*n+j >= 0; z++)
		if (value <= map[i][z*n+j])
			return (false);
	return (true);
}
static bool is_visible_col(std::vector<std::vector<int>> map, \
	int i, int j, int y, int n)
{
	int value = map[i][j];

	for (int z = 1; z*n+i < y && z*n+i >= 0; z++)
		if (value <= map[z*n+i][j])
			return (false);
	return (true);
}

static int is_visible(std::vector<std::vector<int>> map, int i, \
	int j, int x, int y)
{
	if (i == y - 1 || i == 0 || j == x - 1 || j == 0)
		return (1);
	if (is_visible_row(map, i, j, x, -1) || \
		is_visible_row(map, i, j, x, 1) || \
		is_visible_col(map, i, j, y, -1) || \
		is_visible_col(map, i, j, y, 1))
		return (1);
	return (0);
}

int main()
{
	std::vector<std::vector<int>> map;
	int x, y = 0, total = 0;
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
		for (int j = 0; j < x; j++)
			total += is_visible(map, i, j, x, y);

	std::cout << total << " trees are visible from outside the grid" << std::endl;
	return (0);
}