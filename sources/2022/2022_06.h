#ifndef __2022_06__
#define __2022_06__

#include "../shared/Solution.h"

namespace Day06_2022
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static size_t unique_position(const string& input, size_t distinct_chars);
	};
}

#endif
