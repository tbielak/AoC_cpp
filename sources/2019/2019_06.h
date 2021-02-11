#ifndef __2019_06__
#define __2019_06__

#include "../shared/input_output.h"

namespace Day06_2019
{
	class Item
	{
	public:
		Item(const string& input);

		string src;
		string target;
		bool visited;
	};

	typedef vector<Item> t_vecItem;

	t_output main(const t_input& input);
}

#endif
