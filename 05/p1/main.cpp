#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static void init_base_stack(std::string line, int *n_stack, \
	std::vector<std::string> *v)
{
	*n_stack = (line.size() + 1) / 4;
	(*v).resize(*n_stack);
				for (int i = 0; i < *n_stack; i++)
					(*v).push_back("");
}

static void pars_stack(std::vector<std::string> *v, std::string line, \
	int n_stack)
{
	for (int i = 0; i < n_stack; i++)
	{
		if (line[i * 4] == '[')
			(*v)[i].push_back(line[i * 4 + 1]);
	}
}

static std::string::const_iterator get_value_str(std::string *v, \
	std::string::const_iterator it)
{
	while (!std::isdigit(*it))
		it++;
	while (std::isdigit(*it))
	{
		(*v).push_back(*it);
		it++;
	}
	return (it);
}

static void move(std::vector<std::string> *v, std::string line)
{
	int n_move, from, to;
	char c;
	std::string s_n_move, s_from, s_to;
	std::string::const_iterator it = line.begin();

	it = get_value_str(&s_n_move, it);
	it = get_value_str(&s_from, it);
	it = get_value_str(&s_to, it);
	n_move = std::stoi(s_n_move);
	from = std::stoi(s_from) - 1;
	to = std::stoi(s_to) - 1;

	for (int i = 0; i < n_move; i++)
	{
		c = (*v)[from][0];
		(*v)[from].erase(0, 1);
		(*v)[to].insert(0, 1, c);
	}
}

int main()
{
	int n_stack = 0;
	std::ifstream input("input.txt");
	std::string line;
	bool pars_done = false;
	std::vector<std::string> v;

	while(std::getline(input, line))
	{
		if (line.compare("") == 0)
			pars_done = true;
		else if (pars_done == false)
		{
			if (n_stack == 0)
				init_base_stack(line, &n_stack, &v);
			pars_stack(&v, line, n_stack);
		}
		else
			move(&v, line);
	}

	std::cout << "crate that ends up on top of each stack : ";
	for (std::vector<std::string>::iterator it = v.begin() ; it != v.end(); ++it)
		std::cout << (*it)[0];
	std::cout << std::endl;
	return (0);
}