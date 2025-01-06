#ifndef __2024_25__
#define __2024_25__

#include "../shared/Solution.h"

namespace Day25_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);

	private:
		static bool fit(const vector<int>& key, const vector<int>& lock);
	};
}

#endif
