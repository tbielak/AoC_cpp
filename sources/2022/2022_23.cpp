#include "2022_23.h"

namespace Day23_2022
{
	Point::Point(int x /* = INT_MIN */, int y /* = INT_MIN */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Point::valid() const
	{
		return x != INT_MIN;
	}

	bool Main::any_elf_in_adjacent_eight(const set<Point>& pts, const Point& p)
	{
		for (int y = -1; y <= 1; y++)
			for (int x = -1; x <= 1; x++)
				if ((x != 0 || y != 0) && pts.find(Point(p.x + x, p.y + y)) != pts.end())
					return true;

		return false;
	}

	Point Main::propose_move(int cycle, const set<Point>& pts, const Point& p)
	{
		static vector<vector<int>> check = { {-1, 0, 1}, {-1, 0, 1}, {-1, -1, -1}, {1, 1, 1} };
		static vector<int> direction = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; i++)
		{
			int idx_x = (cycle + i) % 4;
			int idx_y = (cycle + i + 2) % 4;

			if (pts.find(Point(p.x + check[idx_x][0], p.y + check[idx_y][0])) == pts.end() &&
				pts.find(Point(p.x + check[idx_x][1], p.y + check[idx_y][1])) == pts.end() &&
				pts.find(Point(p.x + check[idx_x][2], p.y + check[idx_y][2])) == pts.end())
				return Point(p.x + direction[idx_x], p.y + direction[idx_y]);
		}

		return Point();
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// load input
		set<Point> pts;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == '#')
					pts.insert(Point(x, y));

		// do rounds
		int round = 1;
		int after_10_rounds = 0;
		for (; ; round++)
		{
			// propose moves
			map<Point, Point> moves;
			for (const auto& p : pts)
				if (any_elf_in_adjacent_eight(pts, p))
					moves[p] = propose_move(round - 1, pts, p);
				else
					moves[p] = Point();

			// same positions?
			map<Point, int> dst;
			for (const auto& m : moves)
				if (m.second.valid())
					dst[m.second]++;

			for (auto& m : moves)
			{
				const auto& it = dst.find(m.second);
				if (it != dst.end() && it->second > 1)
					m.second = Point();
			}

			// no moves?
			if (dst.size() == 0)
				break;

			// move
			set<Point> t;
			for (const auto& [p, m] : moves)
				t.insert(m.valid() ? m : p);

			pts = move(t);

			// tenth round?
			if (round == 10)
			{
				int xmin = INT_MAX;
				int xmax = INT_MIN;
				int ymin = INT_MAX;
				int ymax = INT_MIN;
				for (const auto& p : pts)
				{
					xmin = min(xmin, p.x);
					ymin = min(ymin, p.y);
					xmax = max(xmax, p.x);
					ymax = max(ymax, p.y);
				}

				for (int x = xmin; x <= xmax; x++)
					for (int y = ymin; y <= ymax; y++)
						if (pts.find(Point(x, y)) == pts.end())
							after_10_rounds++;
			}
		}

		// results
		return make_pair(after_10_rounds, round);
	}
}
