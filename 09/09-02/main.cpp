#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

static void move_head(std::vector<int> *pos_h, int x, int y)
{
	(*pos_h)[0] += x;
	(*pos_h)[1] += y;
}

static void move_rope(std::vector<int> pos_h, std::vector<int> *pos_t)
{
	int dist_x = (*pos_t)[0] - pos_h[0];
	int dist_y = (*pos_t)[1] - pos_h[1];

	if (abs(dist_x) + abs(dist_y) > 2)
	{
		if (dist_x > 0 && dist_y > 0)
		{
			(*pos_t)[0] -= 1;
			(*pos_t)[1] -= 1;
		}
		else if (dist_x > 0 && dist_y < 0)
		{
			(*pos_t)[0] -= 1;
			(*pos_t)[1] += 1;
		}
		else if (dist_x < 0 && dist_y > 0)
		{
			(*pos_t)[0] += 1;
			(*pos_t)[1] -= 1;
		}
		else if (dist_x < 0 && dist_y < 0)
		{
			(*pos_t)[0] += 1;
			(*pos_t)[1] += 1;
		}
	}
	else if (dist_x > 1)
		(*pos_t)[0] -= 1;
	else if (dist_x < -1)
		(*pos_t)[0] += 1;
	else if (dist_y > 1)
		(*pos_t)[1] -= 1;
	else if (dist_y < -1)
		(*pos_t)[1] += 1;
}

int main()
{
	char dir = 0;
	int	n = 0;
	std::vector<int> pos(2, 0);
	std::vector<std::vector<int>> all_pos, all_pos_t;
	std::ifstream input("input.txt");
	std::string line;

	for (int j = 0; j < 11; j++)
		all_pos.push_back(pos);
	all_pos_t.push_back(pos);

	while(std::getline(input, line))
	{
		dir = line[0];
		line.erase(0, 2);
		n = stoi(line);

		for (int i = 0; i < n; i++)
		{
			if (dir == 'L') // left
				move_head(&(all_pos[0]), -1, 0);
			else if (dir == 'R') // righht
				move_head(&(all_pos[0]), 1, 0);
			else if (dir == 'U') // up
				move_head(&(all_pos[0]), 0, -1);
			else if (dir == 'D') // down
				move_head(&(all_pos[0]), 0, 1);
			for (int j = 1; j < 10; j++)
				move_rope(all_pos[j - 1], &(all_pos[j]));
			all_pos_t.push_back(all_pos[9]);
		}
	}

	std::sort(all_pos_t.begin(), all_pos_t.end());
	all_pos_t.erase(std::unique(all_pos_t.begin(), all_pos_t.end()), all_pos_t.end());

	std::cout << "number of ositions that the tail of the rope visit at least once : ";
	std::cout << all_pos_t.size() << std::endl;
	return (0);
}