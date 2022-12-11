#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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
