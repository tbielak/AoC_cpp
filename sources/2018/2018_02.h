#ifndef __2018_02__
#define __2018_02__

#include "../shared/Solution.h"

namespace Day02_2018
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static string diff(const string& s1, const string& s2);
	};
}

#endif
