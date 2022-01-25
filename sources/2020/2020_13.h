#ifndef __2020_13__
#define __2020_13__

#include "../shared/Solution.h"

namespace Day13_2020
{
	typedef pair<int, int> t_bus;	// id, minutes
	typedef vector<t_bus> t_buses;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_buses load(const vector<string>& input);
	};
}

#endif
