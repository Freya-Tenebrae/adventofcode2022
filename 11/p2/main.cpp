#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Item
{
	private:
		int					_base_value;
		std::vector<char>	_op;
		std::vector<int>	_v_op;

	public:
		Item(int value);
		~Item();

		bool	is_div(int modulo);
		void	up_value(char op, int v_op);
};

class Monkey
{
	private:
		std::vector<Item> 	_carriying;
		char 				_op;
		int					_v_op;
		int					_div;
		int					_t;
		int					_f;
		int 				_total_inspected;

	public:
		Monkey(std::vector<Item> carriying, char op, int v_op, \
			int div, int t, int f);
		~Monkey();

		char	getOp();
		int		getTotalInspected();

		void	turn(std::vector<Monkey> *monkey_tribe);
		void	add_item(Item item);
};

Item::Item(int value)
{
	_base_value = value;
}

Item::~Item()
{

}

bool	Item::is_div(int modulo)
{
	int act_val = _base_value;

	std::vector<char>::iterator it_op = _op.begin();
	for (std::vector<int>::iterator it_v_op = _v_op.begin(); \
		it_v_op != _v_op.end(); it_v_op++)
	{
		act_val = act_val % modulo;
		if (*it_op == '+')
			act_val += *it_v_op % modulo;
		else if (*it_op == '*')
		{
			if (*it_v_op == 0)
				act_val *= act_val;
			else
				act_val *= *it_v_op % modulo;
		}
		it_op++;
	}
	if (act_val % modulo == 0)
		return (true);
	return (false);
}

void	Item::up_value(char op, int v_op)
{
	_op.push_back(op);
	_v_op.push_back(v_op);
}

Monkey::Monkey(std::vector<Item> carriying, char op, int v_op, \
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
	for (std::vector<Item>::iterator it=_carriying.begin(); \
		it != _carriying.end(); it++)
	{
		it->up_value(_op, _v_op);

		if (it->is_div(_div) == true)
			(*monkey_tribe)[_t].add_item(*it);
		else
			(*monkey_tribe)[_f].add_item(*it);
		_total_inspected++;
	}
	_carriying.clear();
}

void	Monkey::add_item(Item item)
{
	_carriying.push_back(item);
}

static Monkey pars(std::vector<std::string> details)
{
	std::vector<Item> carriying;
	char op;
	int v_op, div, t, f;

	details[0].erase(0, 18);
	while (details[0].compare("") != 0)
	{
		std::string::size_type pos;
		carriying.push_back(Item(std::stoi(details[0],&pos)));
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

	for (int turn = 0; turn < 10000; turn++)
	{
		for (std::vector<Monkey>::iterator it=monkey_tribe.begin(); \
			it != monkey_tribe.end(); it++)
			it->turn(&monkey_tribe);
		if (turn % 500 == 0 && turn != 0)
		{
			std::cout << "\033[0;35m" << std::setw(5) << turn;
			std::cout << "/10000 done" << "\033[0m" << std::endl;
		}
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
	long long total;


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
	std::cout << "The level of monkey business after 10.000 rounds is :";
	std::cout << total << std::endl;
	return (0);
}
