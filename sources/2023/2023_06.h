#ifndef __2023_06__
#define __2023_06__

#include "../shared/Solution.h"

namespace Day06_2023
{
	using Data = vector<int64_t>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static Data load(const string& s, char after);
		static string remove_spaces(const string& s);
		static int64_t solve(const Data& time, const Data& record);
	};
}

#endif
