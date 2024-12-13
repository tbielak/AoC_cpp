#ifndef __2024_06__
#define __2024_06__

#include "../shared/Solution.h"

namespace Day06_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<int> _move_x, _move_y;

		static pair<int, int> starting_point(const vector<string>& input);
		static size_t walk(const vector<string>& input, const pair<int, int>& sp);
		static bool loop(const vector<string>& input, int x, int y, int ox, int oy);
	};
}

#endif
