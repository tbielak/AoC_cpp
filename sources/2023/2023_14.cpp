#include "2023_14.h"

namespace Day14_2023
{
	void Main::up(vector<string>& m, size_t y, size_t x)
	{
		while (m[y][x] == 'O' && m[y - 1][x] == '.')
		{
			m[y - 1][x] = 'O';
			m[y][x] = '.';

			y--;
			if (y == 0)
				return;
		}
	}

	bool Main::move_north(vector<string>& m)
	{
		for (size_t y = 1; y < m.size(); y++)
			for (size_t x = 0; x < m[0].size(); x++)
				if (m[y][x] == 'O' && m[y - 1][x] == '.')
				{
					up(m, y, x);
					return true;
				}

		return false;
	}

	void Main::tilt(vector<string>& m)
	{
		do {} while (move_north(m));
	}

	size_t Main::sum(const vector<string>& m)
	{
		size_t sum = 0;
		size_t value = m.size();
		for (size_t y = 0; y < m.size(); y++, value--)
			for (size_t x = 0; x < m[0].size(); x++)
				if (m[y][x] == 'O')
					sum += value;

		return sum;
	}

	string stringify(const vector<string>& input)
	{
		string s;
		for (const auto& x : input)
			s += x;
		
		return s;
	}

	vector<string> rotate(const vector<string>& input)
	{
		size_t h = input.size();
		size_t w = input[0].size();
		vector<string> v = vector<string>(w, string(h, '?'));
		for (size_t y = 0; y < h; y++)
			for (size_t x = 0; x < w; x++)
				v[x][w - y - 1] = input[y][x];

		return v;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto m = input;
		tilt(m);
		return sum(m);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto m = input;
		bool cycle_found = false;
		map<string, int64_t> cache;

		constexpr int64_t target = 1000000000;
		for (int64_t step = 0; step != target; step++)
		{
			for (int i = 0; i < 4; i++)
			{
				tilt(m);
				m = rotate(m);
			}

			if (!cycle_found)
			{
				string s = stringify(m);
				auto it = cache.find(s);
				if (it == cache.end())
					cache[s] = step;
				else
				{
					int64_t diff = step - it->second;
					step = ((target - it->second) / diff) * diff + it->second;
					cycle_found = true;
				}
			}
		}

		return sum(m);
	}
}
