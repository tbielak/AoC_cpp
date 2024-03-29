#include "2020_17.h"

namespace Day17_2020
{
	Point4D::Point4D(int x, int y, int z, int w)
	:	x(x), y(y), z(z), w(w)
	{
	}

	Point4D operator+ (Point4D lhs, const Point4D& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;
		return lhs;
	}

	bool Point4D::operator < (const Point4D& rhs) const
	{
		if (x == rhs.x)
		{
			if (y == rhs.y)
			{
				if (z == rhs.z)
					return w < rhs.w;

				return z < rhs.z;
			}

			return y < rhs.y;
		}

		return x < rhs.x;
	}

	const Point4D& Point4D::symetrical()
	{
		z = abs(z);
		w = abs(w);
		return *this;
	}

	PocketDimension::PocketDimension(bool go4d, const vector<string>& input)
	:	_go4d(go4d)
	{
		// init
		_min_x = 0;
		_max_x = int(input[0].size() - 1);
		_min_y = 0;
		_max_y = int(input.size() - 1);
		_max_z = 0;
		_max_w = 0;

		// load
		for (int y = 0; y < (int)input.size(); y++)
		{
			const string& s = input[y];
			for (int x = 0; x < (int)s.size(); x++)
				_cubes[Point4D(x, y, 0, 0)] = (s[x] == '#');
		}

		// generate neighbours
		int wmax = _go4d;
		int wmin = -wmax;
		for (int w = wmin; w <= wmax; w++)
			for (int z = -1; z <= 1; z++)
				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						if (!(x == 0 && y == 0 && z == 0 && w == 0))
							_neighbours.push_back(Point4D(x, y, z, w));
	}

	int PocketDimension::run()
	{
		for (int i = 0; i < 6; i++)
			cycle();

		return count();
	}

	void PocketDimension::cycle()
	{
		t_mapCubes target;
		int wmax = _max_w + _go4d;
		for (int w = 0; w <= wmax; w++)
			for (int z = 0; z <= _max_z + 1; z++)
				for (int y = _min_y - 1; y <= _max_y + 1; y++)
					for (int x = _min_x - 1; x <= _max_x + 1; x++)
						insert(target, Point4D(x, y, z, w));

		swap(_cubes, target);
		inflate();
	}

	void PocketDimension::insert(t_mapCubes& target, const Point4D& center)
	{
		int active = 0;
		for (const auto& n : _neighbours)
			active += _cubes[(center + n).symetrical()];

		target[center] = _cubes[center] ? (active == 2 || active == 3) : active == 3;
	}

	void PocketDimension::inflate()
	{
		_max_x++;
		_max_y++;
		_min_x--;
		_min_y--;
		_max_z++;
		if (_go4d)
			_max_w++;
	}

	int PocketDimension::count() const
	{
		int c = 0;
		for (const auto& x : _cubes)
		{
			const Point4D& p = x.first;
			int v = x.second;
			if (p.z > 0) v *= 2;
			if (p.w > 0) v *= 2;
			c += v;
		}

		return c;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return PocketDimension(false, input).run();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return PocketDimension(true, input).run();
	}
}
