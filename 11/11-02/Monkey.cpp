#include "Monkey.hpp"

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
