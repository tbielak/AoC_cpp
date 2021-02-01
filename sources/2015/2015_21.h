#ifndef __2015_21__
#define __2015_21__

#include "../shared/input_output.h"

namespace Day21_2015
{
	struct Item
	{
		int cost, damage, armor;
	};

	typedef vector<Item> t_vecItem;

	const t_vecItem weapons = { { 8, 4, 0 }, { 10, 5, 0 }, { 25, 6, 0 }, { 40, 7, 0 }, { 74, 8, 0 } };
	const t_vecItem armors = { { 0, 0, 0 }, { 13, 0, 1 }, { 31, 0, 2 }, { 53, 0, 3 }, { 75, 0, 4 }, { 102, 0, 5 } };
	const t_vecItem rings = { { 25, 1, 0 }, { 50, 2, 0 }, { 100, 3, 0 }, { 20, 0, 1 }, { 40, 0, 2 }, { 80, 0, 3 } };

	t_output main(const t_input& input);
}

#endif
