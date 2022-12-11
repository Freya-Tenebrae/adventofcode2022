#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Item.hpp"

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
