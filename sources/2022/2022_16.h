#ifndef __2022_16__
#define __2022_16__

#include "../shared/Solution.h"

namespace Day16_2022
{
	/*
	* Algorithm draft:
	*
	* 1. Load input = load() method:
	*    a) assign numerical ids to valves' names to operate on integers
	*       instead of strings -> see 'names2id' map in load()
	*    b) find relevant valves = valves with flow > 0 + "AA" valve
	*		-> see t_relevant type (vector of valve ids)
	*    c) store flow of each valve in t_flow map: key = valve id; value = flow
	*    d) build graph connecting valves -> t_graph map: key = source valve id,
	*       value = vector of destination valves' ids
	*/

	typedef vector<int> t_relevant;
	typedef map<int, int> t_flow;
	typedef map<int, vector<int>> t_graph;

	/*
	* Algorithm draft (continued):
	*
	* 2. Find shortest routes between every two relevant valves, do not take
	*    flow into account, just assume route length = 1 between two connected valves.
	*
	*    Determine length between valves using bfs(), build final data structure in
	*    shortest_routes().
	* 
	*    Final data structure is t_routes map: key = source valve id, value = vector
	*    of targets, where each target is a pair: target valve id and route length to it
	*    from source valve
	*/

	typedef pair<int, int> t_target;
	typedef map<int, vector<t_target>> t_routes;

	/*
	* * Algorithm draft (continued):
	*
	* 3. Generate all possible paths: start from "AA" and go further in all possible
	*    directions counting cumulated pressure and keeping track of open valves.
	* 
	*    Results are stored in t_paths map: key = bit mask of valves open (meaning
	*    that the solution is limited to 64 valves), value = cumulated pressure
	*/

	typedef map<int64_t, int> t_paths;


	class Solver
	{
	public:
		Solver(const vector<string>& input);
		
		int alone(int time);
		int with_elephant(int time);

	private:
		int _start;
		t_flow _flow;
		t_relevant _relevant;
		t_graph _graph;
		t_routes _routes;
		t_paths _paths;

		void load_input(const vector<string>& input);
		int bfs(int from, int to);
		void shortest_routes();
		void find_paths(int time);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
