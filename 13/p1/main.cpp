#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static std::vector<char> put_v(std::string row)
{
	std::vector<char>	res;
	std::size_t			pos;
	int					n;

	while (row.compare("") != 0)
	{
		if (row[0] == '[' || row[0] == ']')
		{
			pos = 1;
			res.push_back(row[0]);
		}
		else if (row[0] == ',')
		{
			pos = 1;
		}
		else
		{
			n = std::stoi(row, &pos);
			res.push_back('a' + n);
		}
		row.erase(0, pos);
	}
	return (res);
}

static bool compare(std::vector<char> v_l, std::vector<char> v_r)
{
	int lvl_l = 0, lvl_r = 0;
	std::vector<char>::iterator it_l = v_l.begin();
	std::vector<char>::iterator it_r = v_r.begin();

	while (it_l != v_l.end() && it_r != v_r.end())
	{
		while (*it_l == '[')
		{
			lvl_l++;
			it_l++;
		}
		while (*it_r == '[')
		{
			lvl_r++;
			it_r++;
		}
		if (lvl_l != lvl_r)
		{
			if (*it_l == ']' && *it_r != ']')
			{
				std::cout << "l ==]" << std::endl;
				return (true);
			}
			else if (*it_l != ']' && *it_r == ']')
			{
				std::cout << "r ==]" << std::endl;
				return (false);
			}
			else if (*it_l < *it_r)
			{
				std::cout << "lvl_l > lvl_r -> l < r" << std::endl;
				return (true);
			}
			else if (*it_l > *it_r)
			{
				std::cout << "lvl_l > lvl_r -> l > r" << std::endl;
				return (false);
			}
			it_l++;
			it_r++;
			if (lvl_l > lvl_r)
			{
				if (*it_l != ']')
				{
					std::cout << "l ==] && r ==] lvl_l > lvl_r" << std::endl;
					return (false);
				}
			}
			else if (lvl_l < lvl_r)
			{
				if (*it_r != ']')
				{
					std::cout << "l ==] && r ==] lvl_l < lvl_r" << std::endl;
					return (true);
				}
			}
		}
		else
		{
			while (*it_r != ']' && *it_l != ']')
			{
				if (*it_l == ']' && *it_r != ']')
				{
					std::cout << "l ==]" << std::endl;
					return (true);
				}
				else if (*it_l != ']' && *it_r == ']')
				{
					std::cout << "r ==]" << std::endl;
					return (false);
				}
				else if (*it_l < *it_r)
				{
					std::cout << "l < r" << std::endl;
					return (true);
				}
				else if (*it_l > *it_r)
				{
					std::cout << "l > r" << std::endl;
					return (false);
				}
				it_r++;
				it_l++;
			}
			if (*it_l == ']' && *it_r != ']')
			{
				std::cout << "l ==]" << std::endl;
				return (true);
			}
			else if (*it_l != ']' && *it_r == ']')
			{
				std::cout << "r ==]" << std::endl;
				return (false);
			}
			else
			{
				if (lvl_l > lvl_r)
				{
					std::cout << "l ==] && r ==] lvl_l > lvl_r" << std::endl;
					return (false);
				}
				else if (lvl_l < lvl_r)
				{
					std::cout << "l ==] && r ==] lvl_l < lvl_r" << std::endl;
					return (true);
				}
				it_l++;
				it_r++;
			}
		}
	}
	if (it_l == v_l.end() && it_r != v_r.end())
	{
		std::cout << "l end" << std::endl;
		return (true);
	}
	else if (it_l != v_l.end() && it_r == v_r.end())
	{
		std::cout << "r end" << std::endl;
		return (false);
	}
	std::cout << "both end" << std::endl;
	return (true);
}

static bool is_in_right_order(std::string row_l, std::string row_r)
{
	std::vector<char> v_l = put_v(row_l);
	std::vector<char> v_r = put_v(row_r);

	for (std::vector<char>::iterator it = v_l.begin(); it != v_l.end(); it++)
		std::cout << *it;
	std::cout << std::endl;
	for (std::vector<char>::iterator it = v_r.begin(); it != v_r.end(); it++)
		std::cout << *it;
	std::cout << std::endl;
	return (compare(v_l, v_r));
}

int main()
{
	std::ifstream input("input.txt");
	std::string line, row_l, row_r;
	int total = 0, n = 1;

	while(std::getline(input, line))
	{
		row_l = line;
		std::getline(input, line);
		row_r = line;
		std::getline(input, line);
		// std::cout << n << "  ->  ";
		if (is_in_right_order(row_l, row_r) == true)
		{
			std::cout << "true  : +" << n << std::endl;
			// std::cout << "-1" << std::endl;
			total += n;
		}
		else
		{
			// std::cout << "1" << std::endl;
			std::cout << "false : +0" << std::endl;
		}
		// std::cout << std::endl;
		n++;
	}

	std::cout << "The sum of the indices of those pairs is : ";
	std::cout << total << std::endl;
	return (0);
}