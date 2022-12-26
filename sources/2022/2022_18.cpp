#include "2022_18.h"

namespace Day18_2022
{
	Point::Point(int x, int y, int z)
	:	x(x), y(y), z(z)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		if (x == rhs.x)
			return (y == rhs.y) ? z < rhs.z : y < rhs.y;

		return x < rhs.x;
	}

	t_points Main::load(const vector<string>& input)
	{
		t_points points;
		for (const string& s : input)
		{
			int x = stoi(s);
			size_t pos = s.find_first_of(',');
			int y = stoi(s.substr(pos + 1));
			pos = s.find_first_of(',', pos + 1);
			int z = stoi(s.substr(pos + 1));
			points.insert(Point(x, y, z));
		}

		return points;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto points = load(input);

		map<pair<int, int>, set<int>> sx, sy, sz;
		for (const auto& [x, y, z] : points)
		{
			sx[make_pair(y, z)].insert(x);
			sy[make_pair(x, z)].insert(y);
			sz[make_pair(x, y)].insert(z);
		}

		int count = 0;
		for (const auto& [x, y, z] : points)
		{
			const set<int>& vx = sx[make_pair(y, z)];
			const set<int>& vy = sy[make_pair(x, z)];
			const set<int>& vz = sz[make_pair(x, y)];
			if (vx.find(x - 1) == vx.end()) count++;
			if (vx.find(x + 1) == vx.end()) count++;
			if (vy.find(y - 1) == vy.end()) count++;
			if (vy.find(y + 1) == vy.end()) count++;
			if (vz.find(z - 1) == vz.end()) count++;
			if (vz.find(z + 1) == vz.end()) count++;
		}

		return count;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto points = load(input);

		int xmin = INT_MAX;
		int xmax = INT_MIN;
		int ymin = INT_MAX;
		int ymax = INT_MIN;
		int zmin = INT_MAX;
		int zmax = INT_MIN;
		for (const auto& [x, y, z] : points)
		{
			xmin = min(xmin, x - 1);
			ymin = min(ymin, y - 1);
			zmin = min(zmin, z - 1);
			xmax = max(xmax, x + 1);
			ymax = max(ymax, y + 1);
			zmax = max(zmax, z + 1);
		}

		set<Point> visited;
		vector<Point> scan = { Point(xmin, ymin, zmin) };
		static vector<Point> neighbours = { {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1} };

		int count = 0;
		while (scan.size() > 0)
		{
			vector<Point> candidates;
			for (const auto& [x, y, z] : scan)
				for (const auto& [nx, ny, nz] : neighbours)
				{
					Point np(x + nx, y + ny, z + nz);
					if (visited.find(np) == visited.end() &&
						np.x >= xmin && np.x <= xmax && np.y >= ymin && np.y <= ymax && np.z >= zmin && np.z <= zmax)
					{
						if (points.find(np) != points.end())
							count++;
						else
						{
							candidates.push_back(np);
							visited.insert(np);
						}
					}
				}

			scan = move(candidates);
		}

		return count;
	}
}
