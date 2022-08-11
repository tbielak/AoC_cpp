#ifndef __2017_24__
#define __2017_24__

#include "../shared/Solution.h"

namespace Day24_2017
{
	typedef map<int, bool> t_targets;				// target node to visited flag
	typedef map<int, t_targets> t_components;		// source to target nodes

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);	

	private:
		static t_components load(const vector<string>& input);
		static void recursive_check(t_components& components, int current, int strength, int length, int& max_strength, int& max_length);
	};
}

#endif
