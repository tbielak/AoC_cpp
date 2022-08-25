#ifndef __2018_14__
#define __2018_14__

#include "../shared/Solution.h"

namespace Day14_2018
{
	class HotChocolate
	{
	public:
		HotChocolate();

		string ten_recipes(size_t steps);
		size_t how_many_recipes(const string& input);

	private:
		string _recipe;
		int _elf1_pos;
		int _elf2_pos;

		void process();
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
