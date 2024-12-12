#ifndef __2024_02__
#define __2024_02__

#include "../shared/Solution.h"

namespace Day02_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<vector<int>> load(const vector<string>& input);
		static bool is_safe(const vector<int>& v);
	};
}

#endif
