#ifndef __2020_11__
#define __2020_11__

#include "../shared/Solution.h"

namespace Day11_2020
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int adj(const vector<string>& grid, int y, int x);
		static bool go(const vector<string>& grid, int y, int x, int ya, int xa);
		static int see(const vector<string>& grid, int y, int x);
		static int count_them(const vector<string>& grid);
		static int simulate(vector<string> s, int seats_count, int (*func)(const vector<string>&, int, int));
	};
}

#endif
