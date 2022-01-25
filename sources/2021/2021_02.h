#ifndef __2021_02__
#define __2021_02__

#include "../shared/Solution.h"

namespace Day02_2021
{
	typedef vector<pair<char, int64_t>> t_course;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_course load(const vector<string>& input);
	};
}

#endif
