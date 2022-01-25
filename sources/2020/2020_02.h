#ifndef __2020_02__
#define __2020_02__

#include "../shared/Solution.h"

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

	typedef vector<Item> t_items;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_items load(const vector<string>& input);
	};
}

#endif
