#include "2016_01.h"

namespace Day01_2016
{
	Command::Command(int direction, int steps)
	:	direction(direction), steps(steps)
	{
	}

	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	int Point::distance() const
	{
		return ((x < 0) ? -x : x) + ((y < 0) ? - y : y);
	}

	// 0 = north; 1 = east; 2 = south; 3 = west
	const vector<Point> Point::update_position = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

	int part_one(const t_route& route)
	{
		int face = 0;	// 0 = north; 1 = east; 2 = south; 3 = west
		Point pos = Point(0, 0);

		for (const auto& cmd : route)
		{
			face = (face + cmd.direction) & 3;
			pos.x += Point::update_position[face].x * cmd.steps;
			pos.y += Point::update_position[face].y * cmd.steps;
		}

		return pos.distance();
	}

	int part_two(const t_route& route)
	{
		int face = 0;	// 0 = north; 1 = east; 2 = south; 3 = west
		Point pos = Point(0, 0);
		t_visited visited;
		visited.insert(pos);

		for (const auto& cmd : route)
		{
			face = (face + cmd.direction) & 3;

			for (int i = 0; i < cmd.steps; i++)
			{
				pos.x += Point::update_position[face].x;
				pos.y += Point::update_position[face].y;

				const auto& it = visited.find(pos);
				if (it != visited.end())
					return pos.distance();

				visited.insert(pos);
			}
		}

		return -1;
	}

	t_output main(const t_input& input)
	{
		t_route route;
		stringstream ss(input[0]);
		char dir;
		while (ss >> dir)
		{
			int number;
			ss >> number;
			route.push_back(Command(dir == 'R' ? 1 : -1, number));
			ss.ignore(2);
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(route);
		auto p2 = part_two(route);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
