#ifndef __2015_05__
#define __2015_05__

#include "../shared/Solution.h"

namespace Day05_2015
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool nice_part_one(const string& s);
		static bool nice_part_two(const string& s);
	};
}

#endif
