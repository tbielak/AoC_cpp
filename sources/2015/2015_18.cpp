#include "2015_18.h"

namespace Day18_2015
{
	Lights::Lights(const vector<string>& lt)
	:	_lt(lt)
	{
		_width = (int)lt[0].size();
		_height = (int)lt.size();
	}

	void Lights::animate(int part, int steps)
	{
		if (part == 2)
			stuck();

		for (int st = 0; st < steps; st++)
		{
			vector<string> ref = _lt;
			for (int y = 0; y < _height; y++)
				for (int x = 0; x < _width; x++)
				{
					int n = neighbours(ref, x, y);

					if (ref[y][x] == '#')
						_lt[y][x] = (n == 2 || n == 3) ? '#' : '.';
					else
						_lt[y][x] = (n == 3) ? '#' : '.';
				}

			if (part == 2)
				stuck();
		}
	}

	size_t Lights::count_on()
	{
		size_t c = 0;
		for (const auto& s : _lt)
			c += count(s.begin(), s.end(), '#');

		return c;
	}

	void Lights::stuck()
	{
		_lt[0][0] = '#';
		_lt[_height - 1][0] = '#';
		_lt[0][_width - 1] = '#';
		_lt[_height - 1][_width - 1] = '#';
	}

	int Lights::neighbours(const vector<string>& ref, int x, int y)
	{
		int c = 0;
		if (y > 0)
		{
			if (x > 0 && ref[y - 1][x - 1] == '#') c++;
			if (ref[y - 1][x] == '#') c++;
			if (x < _width - 1 && ref[y - 1][x + 1] == '#') c++;
		}
		if (x > 0 && ref[y][x - 1] == '#') c++;
		if (x < _width - 1 && ref[y][x + 1] == '#') c++;
		if (y < _height - 1)
		{
			if (x > 0 && ref[y + 1][x - 1] == '#') c++;
			if (ref[y + 1][x] == '#') c++;
			if (x < _width - 1 && ref[y + 1][x + 1] == '#') c++;
		}

		return c;
	}

	vector<size_t> both_parts(const vector<string>& input)
	{
		vector<size_t> result(2);
		for (int part = 1; part <= 2; part++)
		{
			Lights lights(input);
			lights.animate(part, 100);
			result[part - 1] = lights.count_on();
		}

		return result;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px[0]));
		solutions.push_back(to_string(px[1]));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
