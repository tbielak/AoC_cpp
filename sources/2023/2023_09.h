#ifndef __2023_09__
#define __2023_09__

#include "../shared/Solution.h"

namespace Day09_2023
{
	using Data = vector<int64_t>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Data> load(const vector<string>& input);
		static int64_t extrapolate(Data data, int direction);
		static int64_t solve(const vector<Data>& v, int direction);
	};
}

#endif
