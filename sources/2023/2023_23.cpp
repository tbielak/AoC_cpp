#include "2023_23.h"

namespace Day23_2023
{
	Point::Point(int y, int x)
	:	y(y), x(x)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	bool Point::operator == (const Point& rhs) const
	{
		return y == rhs.y && x == rhs.x;
	}

	static const vector<int> move_x = { 0, 1, 0, -1 };	// down, right, up, left
	static const vector<int> move_y = { 1, 0, -1, 0 };
	static const vector<char> allow = { 'v', '>', '^', '<' };

	vector<int> Main::find_moves(const vector<string>& input, const Point& p, bool ignore_slopes)
	{
		vector<int> directions;
		for (int d = 0; d < 4; d++)
		{
			int x = p.x + move_x[d];
			int y = p.y + move_y[d];
			if (x < 0 || x == (int)input[0].size() || y < 0 || y == (int)input.size())
				continue;

			if (ignore_slopes)
			{
				if (input[y][x] != '#')
					directions.push_back(d);
			}
			else
			{
				if (input[y][x] == '.' || input[y][x] == allow[d])
					directions.push_back(d);
			}
		}

		return directions;
	}

	Crossroad Main::find_crossroads(const vector<string>& input)
	{
		Crossroad crossroad;
		for (int y = 0; y < (int)input[0].size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] != '#')
				{
					Point p(y, x);
					auto directions = find_moves(input, p, true);
					if (directions.size() > 2)
						crossroad[p] = directions;
				}

		return crossroad;
	}

	pair<RouteTarget, bool> Main::find_target(Point p, int d, const vector<string>& input, const Crossroad& crossroads, bool ignore_slopes)
	{
		set<Point> visited = { p };
		vector<int> directions = { d };

		for (int c = 1; ; c++)
		{
			bool no_moves = true;
			for (int d : directions)
			{
				Point np(p.y + move_y[d], p.x + move_x[d]);
				if (visited.find(np) != visited.end())
					continue;

				p = move(np);
				no_moves = false;
				visited.insert(p);
				if (crossroads.find(p) != crossroads.end())
					return make_pair(RouteTarget(p, c), true);

				directions = find_moves(input, p, ignore_slopes);
				break;
			}

			if (no_moves)
				return make_pair(RouteTarget(p, c), false);
		}
	}

	Graph Main::build_graph(const vector<string>& input, const Crossroad& crossroads, bool ignore_slopes)
	{
		Graph g;
		for (const auto& [source, directions] : crossroads)
			for (auto d : directions)
			{
				auto [target, reached] = find_target(source, d, input, crossroads, ignore_slopes);
				if (reached)
					g[source].push_back(target);
			}

		return g;
	}

	void Main::dfs(size_t& max_route, const Graph& graph, const Point& p, const Point& end, size_t length, vector<vector<bool>>& visited)
	{
		visited[p.y][p.x] = true;
		for (const auto& [target, distance] : graph.find(p)->second)
		{
			if (target == end)
				max_route = max(max_route, length + distance);
			else
			if (!visited[target.y][target.x])
				dfs(max_route, graph, target, end, length + distance, visited);
		}

		visited[p.y][p.x] = false;
	}

	size_t Main::solve(const vector<string>& input, bool ignore_slopes)
	{
		int xs = 0;
		while (input[0][xs] != '.') xs++;
		Point start(0, xs);

		int xe = 0;
		while (input[input.size() - 1][xe] != '.') xe++;
		Point end((int)input.size() - 1, xe);

		auto crossroads = find_crossroads(input);
		crossroads[start] = { 0 }; // going down
		crossroads[end] = { }; // no further moves

		auto graph = build_graph(input, crossroads, ignore_slopes);

		size_t max_route = 0;
		vector<vector<bool>> visited = vector<vector<bool>>(input.size(), vector<bool>(input[0].size(), false));
		dfs(max_route, graph, start, end, 0, visited);
		return max_route;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, false);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, true);
	}
}
