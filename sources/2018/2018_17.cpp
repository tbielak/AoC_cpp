#include "2018_17.h"

namespace Day17_2018
{
	Simulation::Simulation(const vector<string>& input)
	{
		int xoffs = INT_MAX;
		int xwidth = INT_MIN;
		_ymin = INT_MAX;
		_ymax = INT_MIN;

		vector<pair<int, int>> clay;
		for (const auto& line : input)
		{
			size_t pos = line.find_first_of(',');
			int vc = stoi(line.substr(2, pos - 2));
			string s = line.substr(pos + 4);
			pos = s.find_first_of("..");
			int vmin = stoi(s.substr(0, pos));
			int vmax = stoi(s.substr(pos + 2));

			if (line[0] == 'x')
			{
				xoffs = min(xoffs, vc);
				xwidth = max(xwidth, vc);
				_ymin = min(_ymin, vmin);
				_ymax = max(_ymax, vmax);
				for (int y = vmin; y <= vmax; y++)
					clay.push_back(make_pair(y, vc));
			}
			else
			{
				xoffs = min(xoffs, vmin);
				xwidth = max(xwidth, vmax);
				_ymin = min(_ymin, vc);
				_ymax = max(_ymax, vc);
				for (int x = vmin; x <= vmax; x++)
					clay.push_back(make_pair(vc, x));
			}
		}

		xoffs--;
		xwidth -= (xoffs - 2);
		_map = vector<string>(_ymax + 2, string(xwidth, '.'));

		for (const auto& [y, x] : clay)
			_map[y][x - xoffs] = '#';

		_xstart = 500 - xoffs;
	}

	void Simulation::run()
	{
		spring(_xstart, 0);
	}

	int Simulation::count(const string& match) const
	{
		int c = 0;
		for (int y = _ymin; y <= _ymax; y++)
			for (char x : _map[y])
				for (char m : match)
					if (x == m)
						c++;

		return c;
	}

	bool Simulation::clay_or_rest_water(int x, int y) const
	{
		return _map[y][x] == '#' || _map[y][x] == '~';
	}

	bool Simulation::falling_water(int x, int y) const
	{
		return _map[y][x] == '|';
	}

	bool Simulation::spread(int& x, int y, int add)
	{
		for (; ; x += add)
		{
			if (!clay_or_rest_water(x, y + 1))
				return true;

			_map[y][x] = '|';

			if (clay_or_rest_water(x + add, y))
				break;
		}

		return false;
	}

	void Simulation::spring(int x, int y)
	{
		_map[y][x] = '|';

		for (; ; y++)
		{
			if (y == _ymax)
				return;

			if (clay_or_rest_water(x, y + 1))
				break;

			_map[y + 1][x] = '|';
		}

		for (; ; y--)
		{
			int xmin = x;
			int xmax = x;
			bool left = spread(xmin, y, -1);
			bool right = spread(xmax, y, 1);

			if (left && !falling_water(xmin, y))
				spring(xmin, y);

			if (right && !falling_water(xmax, y))
				spring(xmax, y);

			if (left || right)
				return;

			for (int x = xmin; x <= xmax; x++)
				_map[y][x] = '~';
		}
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		Simulation sim(input);
		sim.run();
		return make_pair(sim.count("|~"), sim.count("~"));
	}
}
