#ifndef __2024_03__
#define __2024_03__

#include "../shared/Solution.h"

namespace Day03_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool get_number(const string& s, int& left, size_t& pos);
	};
}

#endif
