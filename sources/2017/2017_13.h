#ifndef __2017_13__
#define __2017_13__

#include "../shared/Solution.h"

namespace Day13_2017
{
	typedef map<int, int> t_firewall;	   // <layer, range>

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_firewall load(const vector<string>& input);
		static bool safe(int layer, int range, int delay = 0);
		static bool safe(const t_firewall& firewall, int delay);
	};
}

#endif
