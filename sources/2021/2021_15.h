#ifndef __2021_15_
#define __2021_15__

#include "../shared/input_output.h"

namespace Day15_2021
{
	// main idea:
	// each cavern point (x, y) makes a node in graph
	// node is represented by single int = node index
	// node index is calculated from (x, y) = y * size + x

	typedef pair<int, int> t_intpair;            // <graph node index, risk>
	typedef vector<t_intpair> t_vecintpair;      // vector of destination nodes
	typedef vector<t_vecintpair> t_graph;        // vector of source nodes

	t_output main(const t_input& input);
}

#endif
