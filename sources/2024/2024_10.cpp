#include "2024_10.h"

namespace Day10_2024
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	int Main::ratings(const vector<string>& input, const Point& start, bool distinct)
	{
		int score = 0;
		set<Point> known;
		static vector<int> move_x = { 1, 0, -1, 0 };
		static vector<int> move_y = { 0, 1, 0, -1 };

		queue<pair<Point, int>> q;
		q.push(make_pair(start, 0));
		while (!q.empty())
		{
			auto [p, v] = q.front();
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int x = p.x + move_x[i];
				int y = p.y + move_y[i];
				if (x < 0 || x >= (int)input[y].size() || y < 0 || y >= (int)input.size() || input[y][x] - '0' != v + 1)
					continue;
				
				Point np = Point(x, y);
				if (v + 1 < 9)
				{
					q.push(make_pair(np, v + 1));
					continue;
				}
				
				if (distinct)
					score++;
				else
				{
					auto it = known.find(np);
					if (it == known.end())
					{
						known.insert(np);
						score++;
					}
				}
			}
		}
		
		return score;
	}

	int Main::solve(const vector<string>& input, bool distinct)
	{
		int sum = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == '0')
					sum += ratings(input, Point(x, y), distinct);

		return sum;
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
