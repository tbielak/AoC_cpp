#ifndef __2018_12__
#define __2018_12__

#include "../shared/Solution.h"

namespace Day12_2018
{
	class Solver
	{
	public:
		Solver(const vector<string>& input);
		
		int64_t count(int generations);
		int64_t smart_count(int64_t generations);

	private:
		string _state;
		map<string, char> _notes;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
