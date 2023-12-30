#ifndef __2023_11__
#define __2023_11__

#include "../shared/Solution.h"

namespace Day11_2023
{
	struct Point
	{
		size_t y, x;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<size_t> find_empty_cols(const vector<string>& input);
		static vector<size_t> find_empty_rows(const vector<string>& input);
		static size_t distance(const vector<size_t>& indices, size_t from, size_t to, size_t factor);
		static size_t solve(const vector<string>& input, size_t expand_factor);
	};
}

#endif
