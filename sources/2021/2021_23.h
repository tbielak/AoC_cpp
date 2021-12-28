#ifndef __2021_23__
#define __2021_23__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
