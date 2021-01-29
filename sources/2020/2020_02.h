#ifndef __2020_02__
#define __2020_02__

#include "../shared/input_output.h"

namespace Day02_2020
{
	class Item
	{
	public:
		Item(int min, int max, char letter, const string& password);

		int min;
		int max;
		char letter;
		string password;
	};

	t_output main(const t_input& input);
}

#endif
