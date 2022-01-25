#ifndef __2021_12__
#define __2021_12__

#include "../shared/Solution.h"

namespace Day12_2021
{
	typedef vector<string> t_destinations;           // list of destination nodes
	typedef map<string, t_destinations> t_graph;     // <node, destintion nodes>
	typedef pair<int, int> t_visitedpair;            // <number of visits, number of visits allowed>
	typedef map<string, t_visitedpair> t_visited;    // <node, visited information>
	typedef set<string> t_allpaths;                  // all paths found

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void add(t_graph& graph, const string& from, const string& to);
		static pair<t_graph, t_visited> load(const vector<string>& input);
		static void go(const t_graph& graph, t_visited visited, const string& here_I_am, string path, t_allpaths& all_paths);
	};
}

#endif
