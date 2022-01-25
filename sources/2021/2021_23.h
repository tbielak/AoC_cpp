#ifndef __2021_23__
#define __2021_23__

#include "../shared/Solution.h"

namespace Day23_2021
{
	// Main Idea: simplify the diagram!
	//
	// Diagram looks like this:
	// #############
	// #...........#
	// ###B#C#B#D###
	//   #A#D#C#A#
	//   #########
	//
	// Amphipod can be in room or hallway. Amphipods will never stop on the space
	// immediately outside any room. So we can try to flatten 2D map to 1D map.
	// 1D map has 11 cells: HHRHRHRHRHH, where H is place in hallway, R - room.
	// There is one Amphipod in H place ('A','B','C' or 'D') or the place is empty ('.').
	// There are 0..2 or 0..4 amphipods in R place, examples:
	// - empty room in part one = '..'
	// - full room in part one = 'AD'
	// - partally empty room in part two = '.DCB'
	// Note: empty places are always at the beginning of room contents.
	//
	// Source diagram for part one for example shown above:
	// { ".", ".", "BA", ".", "CD", ".", "BC", ".", "DA", ".", "." }
	// 
	// Target diagram for part one:
	// { ".", ".", "AA", ".", "BB", ".", "CC", ".", "DD", ".", "." }
	// 
	// Target diagram for part two:
	// { ".", ".", "AAAA", ".", "BBBB", ".", "CCCC", ".", "DDDD", ".", "." }

	typedef vector<string> t_diagram;
	typedef queue<t_diagram> t_queue;
	typedef map<t_diagram, int> t_costs_cache;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool is_hallway(const t_diagram& diagram, int place);
		static int target(char amphipod);
		static int cost(char amphipod);
		static bool can_reach(const t_diagram& diagram, int src, int dst);
		static bool target_only(const string& room, char target);
		static vector<int> find_destinations(const t_diagram& diagram, int src);
		static int do_move(const t_diagram& src_diagram, t_diagram& dst_diagram, int src, int dst);
		static int solve(const t_diagram& input, const t_diagram& target);
		static t_diagram load(const vector<string>& input);
	};
}

#endif
