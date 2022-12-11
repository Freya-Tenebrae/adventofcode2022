#include "Monkey.hpp"

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
