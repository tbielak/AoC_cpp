#include "2022_12.h"

namespace Day12_2022
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
		
	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Main::climbing(char from, char to)
	{
		if (from == 'S')
			from = 'a';

		if (to == 'E')
			to = 'z';

		return to <= from + 1;
	}

	int Main::bfs(const vector<string>& input, const Point& start)
	{
		int width = (int)input[0].size();
		int height = (int)input.size();
		const vector<int> move_x = { -1, 1, 0, 0 };
		const vector<int> move_y = { 0, 0, -1, 1 };

		t_visited visited;
		t_queue queue;
		queue.push(make_pair(start, 0));

		while (!queue.empty())
		{
			auto [p, steps] = queue.front();
			queue.pop();

			if (input[p.y][p.x] == 'E')
				return steps;

			if (visited.find(p) == visited.end())
			{
				visited.insert(p);
				for (int i = 0; i < 4; i++)
				{
					int x = p.x + move_x[i];
					int y = p.y + move_y[i];
					if (x >= 0 && x < width && y >= 0 && y < height && climbing(input[p.y][p.x], input[y][x]))
						queue.push(make_pair(Point(x, y), steps + 1));
				}
			}
		}

		return INT_MAX;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == 'S')
					return bfs(input, Point(x, y));

		return -1;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int shortest = INT_MAX;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == 'a')
					shortest = min(shortest, bfs(input, Point(x, y)));

		return shortest;
	}
}
