#ifndef __2021_14__
#define __2021_14__

#include "../shared/Solution.h"

namespace Day14_2021
{
	typedef map<string, int64_t> t_polymer;         // pair of chars -> count
	typedef map<string, char> t_rules;              // pair of chars -> target char
	typedef map<char, int64_t> t_elements;          // char -> count
	typedef map<int64_t, char> t_elements_rev;      // reversed (count -> char)

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int64_t solve(const vector<string>& input, int steps);
	};
}

#endif
