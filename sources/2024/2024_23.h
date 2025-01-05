#ifndef __2024_23__
#define __2024_23__

#include "../shared/Solution.h"

namespace Day23_2024
{
	typedef map<string, set<string>> t_graph;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_graph load(const vector<string>& input);
		static set<string> find_trios(const t_graph& graph);
		static void bron_kerbosch_algorithm(
			set<string>&& R, set<string>&& P, set<string>&& X,
			t_graph& graph, vector<set<string>>& cliques);
	};
}

#endif
