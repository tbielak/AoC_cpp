#ifndef __2022_09__
#define __2022_09__

#include "../shared/Solution.h"

namespace Day09_2022
{
	typedef pair<int, int> t_point;
	typedef set<t_point> t_visited;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_point move_tail(int hx, int hy, int tx, int ty);
		static size_t move_snake(const vector<string>& input, int parts);
	};
}

#endif
