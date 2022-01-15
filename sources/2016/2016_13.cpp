#include "2016_13.h"

namespace Day13_2016
{
	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	int parity(int x) // see https://books.google.pl/books?id=iBNKMspIlqEC&pg=PA76&redir_esc=y&hl=pl#v=onepage&q&f=false
	{
		x = x ^ (x >> 1);
		x = (x ^ (x >> 2)) & 0x11111111;
		return ((x * 0x11111111) >> 28) & 1;
	}

	bool can_go(const Point& p, int fav)
	{
		return !parity(p.x * p.x + 3 * p.x + 2 * p.x * p.y + p.y + p.y * p.y + fav);
	}

	static vector<Point> next_position = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

	void walk(Point me, const Point& dst, t_visited& visited, int fav, int length, int& min_length, t_distinct& distinct, int steps)
	{
		visited[me] = true;

		if (me == dst)
			min_length = min(min_length, length);

		if (length <= steps)
			distinct.insert(me);

		for (int i = 0; i < 4; i++)
		{
			Point next(me.x + next_position[i].x, me.y + next_position[i].y);
			if (next.x < 0 || next.y < 0)
				continue;

			if (can_go(next, fav))
			{
				t_visited::const_iterator it = visited.find(next);
				if (it == visited.end() || !it->second)
					walk(next, dst, visited, fav, length + 1, min_length, distinct, steps);
			}
		}

		visited[me] = false;
	}

	pair<int, int> both_parts(int input)
	{
		Point me(1, 1);
		Point dst(31, 39);
		t_visited visited;
		t_distinct distinct;
		int min_length = INT_MAX;

		walk(me, dst, visited, input, 0, min_length, distinct, 50);
		return make_pair(min_length, (int)distinct.size());
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto bp = both_parts(stoi(input[0]));
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(bp.first));
		solutions.push_back(to_string(bp.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
