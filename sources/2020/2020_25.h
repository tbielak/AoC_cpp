#ifndef __2020_25__
#define __2020_25__

#include "../shared/Solution.h"

namespace Day25_2020
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);

	private:
		static int64_t find_loop_size(int64_t key);
		static int64_t calculate(int64_t key, int64_t loop);
	};
}

#endif
