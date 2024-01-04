#include "2023_18.h"

namespace Day18_2023
{
	Point::Point(int y, int x)
	:	y(y), x(x)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	constexpr int right = 0;
	constexpr int down = 1;
	constexpr int left = 2;
	constexpr int up = 3;

	static const vector<int> move_x = { 1, 0, -1, 0 };
	static const vector<int> move_y = { 0, 1, 0, -1 };

	vector<Item> Main::load(const vector<string>& input, bool hex)
	{
		vector<Item> result;
		static const string directions = "RDLU";
		for (const string& s : input)
		{
			if (hex)
			{
				string h = s.substr(s.find_first_of('#') + 1, 6);

				int v = 0;
				int m = 1 << 16;
				for (int i = 0; i < 5; i++, m >>= 4)
					v += (h[i] <= '9') ? m * (h[i] - '0') : m * (h[i] - 'a' + 10);

				result.push_back({ int(h[5] - '0'), v });
			}
			else
				result.push_back({ int(directions.find_first_of(s[0])), stoi(s.substr(2)) });
		}

		return result;
	}

	set<Point> Main::find_points(const vector<Item>& items)
	{
		Point p(0, 0);
		set<Point> pts;
		pts.insert(p);

		for (const auto& [direction, steps] : items)
		{
			p.x += move_x[direction] * steps;
			p.y += move_y[direction] * steps;
			pts.insert(p);
		}
		
		return pts;
	}

	vector<Range> Main::get_ranges(const set<int>& indices)
	{
		vector<Range> result;
		int prev = *indices.begin();

		for (auto curr : indices)
		{
			if (curr - prev > 1)
				result.push_back(make_pair(prev + 1, curr - 1));

			prev = curr;
			result.push_back(make_pair(prev, prev));
		}

		return result;
	}

	pair<vector<Range>, vector<Range>> Main::get_ranges(const set<Point>& points)
	{
		set<int> x;
		for (const auto& p : points)
			x.insert(p.x);

		set<int> y;
		for (const auto& p : points)
			y.insert(p.y);

		return make_pair(get_ranges(x), get_ranges(y));
	}

	vector<string> Main::compressed_map(const vector<Item>& items, const vector<Range>& rx, const vector<Range>& ry)
	{
		vector<string> m = vector<string>(ry.size(), string(rx.size(), '.'));

		int x = 0;
		while (rx[x].first != 0)
			x++;

		int y = 0;
		while (ry[y].first != 0)
			y++;

		for (auto [direction, steps] : items)
		{
			switch (direction)
			{
			case right: {
				int xx = rx[x].first + steps;
				while (rx[x].first != xx) { m[y][x] = '#'; x++; }
				break;
			}
			case down: {
				int yy = ry[y].first + steps;
				while (ry[y].first != yy) { m[y][x] = '#'; y++; }
				break;
			}
			case left: {
				int xx = rx[x].first - steps;
				while (rx[x].first != xx) { m[y][x] = '#'; x--; }
				break;
			}
			case up: {
				int yy = ry[y].first - steps;
				while (ry[y].first != yy) { m[y][x] = '#'; y--; }
				break;
			}
			}

			m[y][x] = '#';
		}

		return m;
	}

	vector<vector<int64_t>> Main::get_area(const vector<Range>& rx, const vector<Range>& ry)
	{
		vector<vector<int64_t>> area = vector<vector<int64_t>>(ry.size(), vector<int64_t>(rx.size(), 0));
		for (size_t y = 0; y < ry.size(); y++)
			for (size_t x = 0; x < rx.size(); x++)
				area[y][x] = int64_t(rx[x].second - rx[x].first + 1) * int64_t(ry[y].second - ry[y].first + 1);

		return area;
	}

	bool Main::can_go(const vector<string>& m, int y, int x)
	{
		return x >= 0 && x < (int)m[0].size() && y >= 0 && y < (int)m.size() && m[y][x] == '#';
	}

	vector<vector<int>> Main::walk(const vector<string>& input)
	{
		vector<vector<int>> dmap = vector<vector<int>>(input.size(), vector<int>(input[0].size(), 0));

		int start_y = 0;
		int start_x = 0;
		while (input[start_y][start_x] != '#') start_x++;

		int x = start_x;
		int y = start_y;
		int direction = right;
		while (1)
		{
			dmap[y][x] = (1 << direction);

			int nx = x + move_x[direction];
			int ny = y + move_y[direction];
			if (can_go(input, ny, nx))
			{
				x = nx;
				y = ny;
			}
			else
			{
				switch (direction)
				{
				case right:
				case left:
				{
					if (can_go(input, y - 1, x)) { y--; direction = up; break; }
					if (can_go(input, y + 1, x)) { y++; direction = down; break; }
					break;
				}
				case down:
				case up:
				{
					if (can_go(input, y, x - 1)) { x--; direction = left; break; }
					if (can_go(input, y, x + 1)) { x++; direction = right; break; }
					break;
				}
				}
			}

			if (x == start_x && y == start_y)
				break;
		}

		return dmap;
	}

	int64_t Main::count(const vector<string>& cmap, vector<vector<int>>& dmap, const vector<vector<int64_t>>& area)
	{
		int64_t result = 0;
		for (size_t y = 0; y < cmap.size(); y++)
		{
			int x = 0;
			while (x < (int)cmap[0].size())
			{
				int b = x;
				while (x < (int)cmap[0].size() && cmap[y][x] == '.')
					x++;

				if (x == (int)cmap[0].size())
					break;

				int64_t c = x - b;
				if (x > 0 && y > 0 && b > 0 && c > 0)
				{
					int v = dmap[y - 1][b];
					if ((v & down) > 0)
					{
						for (int i = b; i < x; i++)
						{
							dmap[y][i] |= v;
							result += area[y][i];
						}
					}
				}

				while (x < (int)cmap[0].size() && cmap[y][x] == '#')
					result += area[y][x++];
			}
		}

		return result;
	}

	int64_t Main::solve(const vector<string>& input, bool hex)
	{
		auto items = load(input, hex);
		auto points = find_points(items);
		auto ranges = get_ranges(points);
		auto cmap = compressed_map(items, ranges.first, ranges.second);
		auto dmap = walk(cmap);
		auto area = get_area(ranges.first, ranges.second);
		return count(cmap, dmap, area);
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
