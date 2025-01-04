#ifndef __2024_22__
#define __2024_22__

#include "../shared/Solution.h"

namespace Day22_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<int64_t> load(const vector<string>& input);
		static int64_t next(int64_t v);
	};
}

#endif
