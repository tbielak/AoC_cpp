#ifndef __2021_15_
#define __2021_15__

#include "../shared/Solution.h"

namespace Day15_2021
{
	// main idea:
	// each cavern point (x, y) makes a node in graph
	// node is represented by single int = node index
	// node index is calculated from (x, y) = y * size + x

	typedef pair<int, int> t_intpair;            // <graph node index, risk>
	typedef vector<t_intpair> t_vecintpair;      // vector of destination nodes
	typedef vector<t_vecintpair> t_graph;        // vector of source nodes

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int find_lowest_risk(const t_graph& graph, int gsize);
		static int succ(int r);
		static int solve(const vector<string>& input, int enlarge = 1);
	};
}

#endif
