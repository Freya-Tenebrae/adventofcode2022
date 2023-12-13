#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

class Monkey
{
	private:
		std::vector<int> 	_carriying;
		char 				_op;
		int					_v_op;
		int					_div;
		int					_t;
		int					_f;
		int 				_total_inspected;

	public:
		Monkey(std::vector<int> carriying, char op, int v_op, \
			int div, int t, int f);
		~Monkey();

		char	getOp();
		int		getTotalInspected();

		void	turn(std::vector<Monkey> *monkey_tribe);
		void	add_item(int item);
};

Monkey::Monkey(std::vector<int> carriying, char op, int v_op, \
	int div, int t, int f)
{
	_carriying = carriying;
	_op = op;
	_v_op = v_op;
	_div = div;
	_t = t;
	_f = f;
	_total_inspected = 0;
}

Monkey::~Monkey()
{

}

char	Monkey::getOp()
{
	return (_op);
}

int	Monkey::getTotalInspected()
{
	return (_total_inspected);
}


void	Monkey::turn(std::vector<Monkey> *monkey_tribe)
{
	for (std::vector<int>::iterator it=_carriying.begin(); \
		it != _carriying.end(); it++)
	{
		if (_op == '+')
			*it += _v_op;
		else if (_op == '*')
		{
			if (_v_op == 0)
				*it *= *it;
			else
				*it *= _v_op;
		}
		*it /= 3;

		if (*it % _div == 0)
			(*monkey_tribe)[_t].add_item(*it);
		else
			(*monkey_tribe)[_f].add_item(*it);
		_total_inspected++;
	}
	_carriying.clear();
}

void	Monkey::add_item(int item)
{
	_carriying.push_back(item);
}


static Monkey pars(std::vector<std::string> details)
{
	std::vector<int> carriying;
	char op;
	int v_op, div, t, f;

	details[0].erase(0, 18);
	while (details[0].compare("") != 0)
	{
		std::string::size_type pos;
		carriying.push_back(std::stoi(details[0],&pos));
		details[0].erase(0, pos);
		details[0].erase(0, 2);
	}

	details[1].erase(0, 23);
	op = details[1][0];
	details[1].erase(0, 2);
	if (details[1].compare("old") == 0)
		v_op = 0;
	else
		v_op = std::stoi(details[1]);

	details[2].erase(0, 21);
	div = std::stoi(details[2]);

	details[3].erase(0, 29);
	t = std::stoi(details[3]);

	details[4].erase(0, 30);
	f = std::stoi(details[4]);

	return (Monkey(carriying, op, v_op, div, t, f));
}

static std::vector<int> process(std::vector<Monkey> monkey_tribe)
{
	int	n_monkey = 0;
	std::vector<int> n_inspected;

	for (int turn = 0; turn < 20; turn++)
	{
		for (std::vector<Monkey>::iterator it=monkey_tribe.begin(); \
			it != monkey_tribe.end(); it++)
			it->turn(&monkey_tribe);
	}

	for (std::vector<Monkey>::iterator it=monkey_tribe.begin(); \
			it != monkey_tribe.end(); it++)
	{
		std::cout << "monkey " << n_monkey << " : ";
		std::cout << it->getTotalInspected() << std::endl;
		n_inspected.push_back(it->getTotalInspected());
		n_monkey++;
	}

	return (n_inspected);
}

int main()
{
	std::ifstream input("input.txt");
	std::string line;
	std::vector<Monkey> monkey_tribe;
	std::vector<std::string> details;
	std::vector<int> n_inspected;
	int total;


	while(std::getline(input, line))
	{
		std::getline(input, line);
		details.push_back(line.substr());
		std::getline(input, line);
		details.push_back(line.substr());
		std::getline(input, line);
		details.push_back(line.substr());
		std::getline(input, line);
		details.push_back(line.substr());
		std::getline(input, line);
		details.push_back(line.substr());
		monkey_tribe.push_back(pars(details));
		details.clear();
		std::getline(input, line);
	}

	n_inspected = process(monkey_tribe);

	std::sort(n_inspected.begin(), n_inspected.end());
	total = n_inspected.back();
	n_inspected.pop_back();
	total *= n_inspected.back();
	std::cout << "The level of monkey business after 20 rounds is : ";
	std::cout << total << std::endl;
	return (0);
}
