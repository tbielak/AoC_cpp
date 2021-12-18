#ifndef __2021_12__
#define __2021_12__

#include "../shared/input_output.h"

namespace Day12_2021
{
	typedef vector<string> t_destinations;           // list of destination nodes
	typedef map<string, t_destinations> t_graph;     // <node, destintion nodes>
	typedef pair<int, int> t_visitedpair;            // <number of visits, number of visits allowed>
	typedef map<string, t_visitedpair> t_visited;    // <node, visited information>
	typedef set<string> t_allpaths;                  // all paths found

	t_output main(const t_input& input);
}

#endif
