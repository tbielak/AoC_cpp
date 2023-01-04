#include "2018_18.h"

namespace Day18_2018
{
	LumberCollection::LumberCollection(const vector<string>& input)
	:	_area(input)
	{
		_width = (int)_area[0].size();
		_height = (int)_area.size();
	}

	int LumberCollection::run(int minutes)
	{
		map<string, int> cache;
		bool pattern_found = false;

		for (int m = 0; m < minutes; m++)
		{
			if (!pattern_found)
			{
				string key;
				for (const auto& s : _area)
					key += s;

				const auto& it = cache.find(key);
				if (it == cache.end())
					cache[key] = m;
				else
				{
					pattern_found = true;
					int diff = m - it->second;
					m += ((minutes - m) / diff) * diff;
				}
			}

			vector<string> next = _area;
			for (int y = 0; y < _height; y++)
				for (int x = 0; x < _width; x++)
				{
					if (_area[y][x] == '.' && adjacent(x, y, '|') >= 3)
						next[y][x] = '|';

					if (_area[y][x] == '|' && adjacent(x, y, '#') >= 3)
						next[y][x] = '#';

					if (_area[y][x] == '#' && (adjacent(x, y, '#') == 0 || adjacent(x, y, '|') == 0))
						next[y][x] = '.';
				}

			_area = move(next);
		}

		return count('|') * count('#');
	}

	int LumberCollection::adjacent(int x, int y, char match) const
	{
		int c = 0;
		for (int dy = -1; dy <= 1; dy++)
			for (int dx = -1; dx <= 1; dx++)
			{
				if (dy == 0 && dx == 0)
					continue;

				int nx = x + dx;
				int ny = y + dy;
				if (nx >= 0 && nx < _width && ny >= 0 && ny < _height && _area[ny][nx] == match)
					c++;
			}

		return c;
	}

	int LumberCollection::count(char match) const
	{
		int c = 0;
		for (const string& s : _area)
			for (char x : s)
				if (x == match)
					c++;

		return c;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return LumberCollection(input).run(10);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return LumberCollection(input).run(1000000000);
	}
}
