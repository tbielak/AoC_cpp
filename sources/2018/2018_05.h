#ifndef __2018_05__
#define __2018_05__

#include "../shared/Solution.h"

namespace Day05_2018
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static bool keep(char a, char b);
		static size_t react_length(const string& input, char skip = 0);
	};
}

#endif
