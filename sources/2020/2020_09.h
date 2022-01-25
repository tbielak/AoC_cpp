#ifndef __2020_09__
#define __2020_09__

#include "../shared/Solution.h"

namespace Day09_2020
{
	const int64_t preamble = 25;
	typedef vector<int64_t> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_data load(const vector<string>& input);
		static bool valid(const t_data& data, int64_t n);
	};
}

#endif
