#include "Item.hpp"

Item::Item(int value)
{
	_base_value = value;
}

Item::~Item()
{

}

bool	Item::is_div(int modulo)
{
	int act_val = _base_value, tmp_value;

	std::vector<char>::iterator it_op = _op.begin();
	for (std::vector<int>::iterator it_v_op = _v_op.begin(); \
		it_v_op != _v_op.end(); it_v_op++)
	{
		act_val = act_val % modulo;
		tmp_value = *it_v_op % modulo;

		if (*it_op == '+')
			act_val += tmp_value;
		else if (*it_op == '*')
		{
			if (*it_v_op == 0)
				act_val *= act_val;
			else
				act_val *= tmp_value;
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
