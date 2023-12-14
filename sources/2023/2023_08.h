#ifndef __2023_08__
#define __2023_08__

#include "../shared/Solution.h"

namespace Day08_2023
{
	using Network = map<string, pair<string, string>>;

	struct Data
	{
		string directions;
		Network network;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static Data load(const vector<string>& input);
		static int solve(const Data& data, string node);
		static int64_t greatest_common_divisor(int64_t a, int64_t b);
		static int64_t least_common_multiple(int64_t a, int64_t b);
	};
}

#endif
