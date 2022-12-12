#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

static std::vector<int> pars(std::string line, std::vector<int> *pos, \
	std::vector<int> *end, int y, int *x)
{
	std::vector<int> row;
	for(std::string::const_iterator it = line.begin(); it != line.end(); ++it)
	{
		if (*it == 'S')
		{
			pos->push_back(y);
			pos->push_back(*x);
			row.push_back(0);
		}
		else if (*it == 'E')
		{
			end->push_back(y);
			end->push_back(*x);
			row.push_back(25);
		}
		else
			row.push_back(*it - 'a');
		(*x)++;
	}
	return (row);
}

static void put_dist(std::vector<std::vector<int>> map, \
	std::vector<std::vector<int>> *dist_from_exit, \
	int source_y, int source_x, int y, int x, int value)
{
	if ((*dist_from_exit)[y][x] == 0)
	{
		if (map[y][x] >= map[source_y][source_x] - 1)
			(*dist_from_exit)[y][x] = value;
	}
}

static void next_pos(std::vector<std::vector<int>>map, \
	std::vector<std::vector<int>> *dist_from_exit, \
	int x_max, int y_max, int value)
{
	for (int y = 0; y < y_max; y++)
	{
		for (int x = 0; x < x_max; x++)
		{
			if ((*dist_from_exit)[y][x] == value)
			{
				if (x > 0)
					put_dist(map, dist_from_exit, y, x, y, x - 1, value + 1);
				if (x < x_max - 1)
					put_dist(map, dist_from_exit, y, x, y, x + 1, value + 1);
				if (y > 0)
					put_dist(map, dist_from_exit, y, x, y - 1, x, value + 1);
				if (y < y_max - 1)
					put_dist(map, dist_from_exit, y, x, y + 1, x, value + 1);
			}
		}
	}
}

static void put_dist_only_a(std::vector<std::vector<int>> map, \
	std::vector<std::vector<int>> *map_only_a, \
	int source_y, int source_x, int y, int x, int value)
{
	if ((*map_only_a)[y][x] == 0)
	{
		if (map[y][x] == map[source_y][source_x])
			(*map_only_a)[y][x] = value;
	}
}

static void next_pos_only_a(std::vector<std::vector<int>>map, \
	std::vector<std::vector<int>> *map_only_a, \
	int x_max, int y_max, int value)
{
	for (int y = 0; y < y_max; y++)
	{
		for (int x = 0; x < x_max; x++)
		{
			if ((*map_only_a)[y][x] == value)
			{
				if (x > 0)
					put_dist_only_a(map, map_only_a, y, x, y, x - 1, value + 1);
				if (x < x_max - 1)
					put_dist_only_a(map, map_only_a, y, x, y, x + 1, value + 1);
				if (y > 0)
					put_dist_only_a(map, map_only_a, y, x, y - 1, x, value + 1);
				if (y < y_max - 1)
					put_dist_only_a(map, map_only_a, y, x, y + 1, x, value + 1);
			}
		}
	}
}

static bool is_full(std::vector<std::vector<int>> vv)
{
	for (std::vector<std::vector<int>>::iterator it_y = vv.begin(); \
		it_y != vv.end(); ++it_y)
	{
		for (std::vector<int>::iterator it = it_y->begin(); it != it_y->end(); ++it)
		{
			if (*it == 0)
				return (false);
		}
	}
	return (true);
}

static std::vector<std::vector<int>> move_on_a(std::vector<std::vector<int>> map, \
	std::vector<int> pos, int x_max, int y_max)
{
	std::vector<std::vector<int>> map_only_a, to_send;
	std::vector<int> tmp;
	map_only_a = map;
	int value = 1;

	for (std::vector<std::vector<int>>::iterator it_y = map_only_a.begin(); \
		it_y != map_only_a.end(); ++it_y)
	{
		for (std::vector<int>::iterator it = it_y->begin(); it != it_y->end(); ++it)
		{
			if (*it != 0)
				*it = -1;
		}
	}

	map_only_a[pos[0]][pos[1]] = 1;
	while (is_full(map_only_a) == false && value < x_max * y_max)
	{
		next_pos_only_a(map, &map_only_a, x_max, y_max, value);
		value += 1;
	}

	for (int y = 0; y < y_max; y++)
	{
		for (int x = 0; x < x_max; x++)
		{
			if (map_only_a[y][x] > 0)
			{
				tmp.push_back(y);
				tmp.push_back(x);
				to_send.push_back(tmp);
				tmp.clear();
			}
		}
	}
	return (to_send);
}

static int move_to_exit(std::vector<std::vector<int>> map, \
	std::vector<std::vector<int>> dist_from_exit, std::vector<int> pos, \
	int x_max, int y_max)
{
	int value = 1;
	std::vector<int> result;
	std::vector<std::vector<int>> all_start_possible;

	(void)pos;

	while (is_full(dist_from_exit) == false && value < x_max * y_max)
	{
		next_pos(map, &dist_from_exit, x_max, y_max, value);
		value += 1;
	}
	all_start_possible = move_on_a(map, pos, x_max, y_max);
	for (std::vector<std::vector<int>>::iterator it = all_start_possible.begin(); \
		it != all_start_possible.end(); ++it)
	{
		if (dist_from_exit[(*it)[0]][(*it)[1]] < value)
		value = dist_from_exit[(*it)[0]][(*it)[1]];
	}
	return (value);
}

int main()
{
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::vector<int>> map, dist_from_exit;
	std::vector<int> pos, end, row;
	int y = 0, x = 0, total_movement = 0;

	while(std::getline(input, line))
	{
		x = 0;
		row = pars(line, &pos, &end, y, &x);
		map.push_back(row);
		for (std::vector<int>::iterator it = row.begin(); it != row.end(); ++it)
			*it = 0;
		dist_from_exit.push_back(row);
		y++;
	}

	dist_from_exit[end[0]][end[1]] = 1;
	total_movement = move_to_exit(map, dist_from_exit, pos, x, y) - 1;

	std::cout << "The fewest steps required to move from your current position to the location that should get the best signal is : ";
	std::cout << total_movement << std::endl;
	return (0);
}