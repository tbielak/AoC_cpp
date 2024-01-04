#include "2023_16.h"

namespace Day16_2023
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
	
	Beam::Beam(const Point& p, int h)
	:	p(p), h(h)
	{
	}

	bool Beam::operator < (const Beam& rhs) const
	{
		return (p == rhs.p) ? h < rhs.h : p < rhs.p;
	}

	constexpr int right = 0;
	constexpr int down = 1;
	constexpr int left = 2;
	constexpr int up = 3;

	size_t Main::solve(const vector<string>& input, const Beam& b)
	{
		vector<Point> mv = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

		set<Beam> visited;
		vector<Beam> beams;
		beams.push_back(b);

		set<Point> energized;
		while (beams.size() > 0)
		{
			vector<Beam> output;
			for (const auto& b : beams)
			{
				auto it = visited.find(b);
				if (it != visited.end())
					continue;

				visited.insert(b);
				
				auto [p, h] = b;
				energized.insert(p);

				auto [y, x] = p;
				switch (input[y][x])
				{
					case '/': h ^= 3; break;
					case '\\': h ^= 1; break;
					case '|':
					{
						if (y > 0)
							output.push_back(Beam(Point(y - 1, x), up));

						h = down;
						break;
					}
					case '-':
					{
						if (x > 0)
							output.push_back(Beam(Point(y, x - 1), left));

						h = right;
						break;
					}
				}

				y += mv[h].y;
				x += mv[h].x;
				if (y >= 0 && y < (int)input.size() && x >= 0 && x < (int)input[0].size())
					output.push_back(Beam(Point(y, x), h));
			}

			beams = move(output);
		}

		return energized.size();
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, Beam(Point(0, 0), right));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		vector<Beam> beams;
		for (int x = 0; x < (int)input[0].size(); x++)
		{
			beams.push_back(Beam(Point(0, x), down));
			beams.push_back(Beam(Point((int)input.size() - 1, x), up));
		}

		for (int y = 0; y < (int)input.size(); y++)
		{
			beams.push_back(Beam(Point(y, 0), right));
			beams.push_back(Beam(Point(y, (int)input[0].size() - 1), left));
		}

		size_t result = 0;
		for (const auto& b : beams)
			result = max(result, solve(input, b));

		return result;
	}
}
