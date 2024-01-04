#include "2023_17.h"

namespace Day17_2023
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

	State::State(const Point& p, int d, int c)
	:	point(p), direction(d), count(c)
	{
	}

	bool State::operator < (const State& rhs) const
	{
		if (point == rhs.point)
			return (direction == rhs.direction) ? count < rhs.count : direction < rhs.direction;
		
		return point < rhs.point;
	}

	Distance::Distance(int v /* = INT_MAX */)
	:	value(v)
	{
	}

	bool Distance::operator < (const Distance& rhs) const
	{
		return value < rhs.value;
	}
	
	bool Distance::operator > (const Distance& rhs) const
	{
		return value > rhs.value;
	}

	Distance::operator int() const
	{
		return value;
	}

	vector<State> Main::adjacent(const State& s, int cmin, int cmax)
	{
		static const vector<int> move_x = { 0, 1, 0, -1 };
		static const vector<int> move_y = { 1, 0, -1, 0 };

		vector<State> adj;
		if (s.count >= cmin)
		{
			// 90-deg turns
			int d1 = (s.direction + 3) % 4;
			adj.push_back(State(Point(s.point.y + move_y[d1], s.point.x + move_x[d1]), d1, 1));

			int d2 = (s.direction + 1) % 4;
			adj.push_back(State(Point(s.point.y + move_y[d2], s.point.x + move_x[d2]), d2, 1));
		}

		if (s.count < cmax)
			// continue moving forward
			adj.push_back(State(Point(s.point.y + move_y[s.direction], s.point.x + move_x[s.direction]), s.direction, s.count + 1));

		return adj;
	}

	map<State, Distance> Main::dijkstra(const vector<string>& input, int cmin, int cmax, int height, int width)
	{
		map<State, Distance> dk;
		priority_queue<pair<Distance, State>, vector<pair<Distance, State>>, greater<pair<Distance, State>>> pq;

		for (int direction = 0; direction < 4; direction++)
		{
			State s(Point(0, 0), direction, 0);
			dk[s] = 0;
			pq.push({ 0, s });
		}

		while (!pq.empty())
		{
			auto [distance, state] = pq.top();
			pq.pop();

			if (distance > dk[state])
				continue;

			for (const auto& ns: adjacent(state, cmin, cmax))
			{
				if (ns.point.y < 0 || ns.point.y >= height || ns.point.x < 0 || ns.point.x >= width)
					continue;

				int new_distance = dk[state] + input[ns.point.y][ns.point.x] - '0';
				if (int(dk[ns]) > new_distance)
				{
					dk[ns] = new_distance;
					pq.push({ new_distance, ns });
				}
			}
		}

		return dk;
	}

	int Main::solve(const vector<string>& input, int cmin, int cmax)
	{
		int height = (int)input.size();
		int width = (int)input[0].size();
		auto dk = dijkstra(input, cmin, cmax, height, width);
		
		int result = INT_MAX;
		for (int direction = 0; direction < 4; direction++)
			for (int count = cmin; count <= cmax; count++)
				result = min(result, int(dk[State(Point(height - 1, width - 1), direction, count)]));

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, 0, 3);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 4, 10);
	}
}
