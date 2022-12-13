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

static void is_in_right_order(std::vector<std::vector<char> > &signals, std::string signal)
{
	std::vector<char> v_signal = put_v(signal);
	bool is_placed = false;

	if (signals.empty() == true)
	{
		signals.push_back(v_signal);
	}
	else
	{
		for(std::vector<std::vector<char> >::iterator it = signals.begin(); it != signals.end(); ++it)
		{
			if (compare(v_signal, *it))
			{
				signals.insert(it, v_signal);
				std::cout << "placed" << std::endl;
				is_placed = true;
				break;
			}
		}
		if (is_placed == false)
			signals.insert(signals.end(), v_signal);
	}
}

int main()
{
	std::ifstream input("input.txt");
	std::string line, row_l, row_r, sig2 = "[[2]]", sig6 = "[[6]]";
	std::vector<std::vector<char> > signals;
	std::vector<char> v_sig2, v_sig6;
	int total = 1, n = 1;

	while(std::getline(input, line))
	{
		row_l = line;
		std::getline(input, line);
		row_r = line;
		std::getline(input, line);
		is_in_right_order(signals, row_l);
		is_in_right_order(signals, row_r);
	}
	is_in_right_order(signals, sig2);
	is_in_right_order(signals, sig6);

	v_sig2 = put_v(sig2);
	v_sig6 = put_v(sig6);

	std::cout << "search" << std::endl;
	for(std::vector<std::vector<char> >::iterator it = signals.begin(); it != signals.end(); ++it)
	{
		if (std::equal(it->begin(), it->end(), v_sig2.begin()) == true || \
			std::equal(it->begin(), it->end(), v_sig6.begin()) == true)
		{
			std::cout << "found" << std::endl;
			std::cout << n << std::endl;
			total *= n;
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
		n++;
	}

	std::cout << "The decoder key for the distress signal is : ";
	std::cout << total << std::endl;
	return (0);
}