#ifndef __2021_24__
#define __2021_24__

#include "../shared/Solution.h"

namespace Day24_2021
{
	class Solver
	{
	public:
		Solver(const vector<string>& input, int w_init);

		string execute();

	private:
		int _w_init;
		int _step;
		vector<int> _A, _B, _C, _w;
		vector<int64_t> _max_z;

		int64_t execute_block(int64_t z, size_t i);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
