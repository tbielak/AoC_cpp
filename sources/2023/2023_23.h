#ifndef __2023_23__
#define __2023_23__

#include "../shared/Solution.h"

namespace Day23_2023
{
	class Point
	{
	public:
		Point(int y, int x);
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;

		int y, x;
	};

	using Crossroad = map<Point, vector<int>>;	// map source point to directions
	using RouteTarget = pair<Point, int>;		// map target point to distance
	using Graph = map<Point, vector<RouteTarget>>;	// map source to targets (with distances)

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<int> find_moves(const vector<string>& input, const Point& p, bool ignore_slopes);
		static Crossroad find_crossroads(const vector<string>& input);
		static pair<RouteTarget, bool> find_target(Point p, int d, const vector<string>& input, const Crossroad& crossroads, bool ignore_slopes);
		static Graph build_graph(const vector<string>& input, const Crossroad& crossroads, bool ignore_slopes);
		static void dfs(size_t& max_route, const Graph& graph, const Point& p, const Point& end, size_t length, vector<vector<bool>>& visited);
		static size_t solve(const vector<string>& input, bool ignore_slopes);
	};
}

#endif
