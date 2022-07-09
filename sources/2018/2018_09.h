#ifndef __2018_09__
#define __2018_09__

#include "../shared/Solution.h"

namespace Day09_2018
{
	class Marble
	{
	public:
		Marble(int number);

		int number;
		Marble* prev;
		Marble* next;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static pair<int, int> load(const string& input);
		static int64_t solve(int players, int last_marble);
	};
}

#endif
