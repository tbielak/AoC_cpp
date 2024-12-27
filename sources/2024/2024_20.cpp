#include "2024_20.h"

namespace Day20_2024
{
	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	Racetrack::Racetrack(const vector<string>& input)
	{
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == 'S')
					_path.push_back(Point(x, y));

		vector<int> move_x = { 1, 0, -1, 0 };
		vector<int> move_y = { 0, 1, 0, -1 };
		do
		{
			for (int d = 0; d < 4; d++)
			{
				Point np(_path.back().x + move_x[d], _path.back().y + move_y[d]);
				if (_path.size() > 1 && _path[_path.size() - 2] == np)
					continue;

				if (input[np.y][np.x] != '#')
				{
					_path.push_back(np);
					break;
				}

			}
		} while (input[_path.back().y][_path.back().x] != 'E');

		for (int i = 0; i < (int)_path.size(); i++)
			_points[_path[i]] = i;
	}

	int Racetrack::cheat_count(int cheat_length, int requested_saving) const
	{
		int c = 0;
		for (int i = 0; i < (int)_path.size(); i++)
			for (int j = i + 1; j < (int)_path.size(); j++)
			{
				int distance = manhattan_distance(_path[i], _path[j]);
				if (distance <= cheat_length)
					if (iabs(step(_path[i]) - step(_path[j])) >= requested_saving + distance)
						c++;
			}

		return c;
	}

	int Racetrack::iabs(int x) const
	{
		return (x < 0) ? -x : x;
	}

	int Racetrack::manhattan_distance(const Point& a, const Point& b) const
	{
		return iabs(a.x - b.x) + iabs(a.y - b.y);
	}

	int Racetrack::step(const Point& p) const
	{
		return _points.find(p)->second;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Racetrack(input).cheat_count(2, 100);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Racetrack(input).cheat_count(20, 100);
	}
}
