#ifndef __2018_11__
#define __2018_11__

#include "../shared/Solution.h"

namespace Day11_2018
{
	class Grid
	{
	public:
		Grid(const string& serial_number);
		
		string solve(int smin, int smax) const;

	private:
		vector<vector<int>> _grid;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
