#include "2020_03.h"

namespace Day03_2020
{
	size_t part_one(const vector<string>& input)
	{
		size_t x = 0;
		size_t c = 0;
		for (const auto& s : input)
		{
			if (s[x] == '#') c++;
			x = (x + 3) % input[0].size();
		}

		return c;
	}

	uintmax_t part_two(const vector<string>& input)
	{
		const vector<pair<size_t, size_t>> slopes = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

		uintmax_t m = 1;
		for (const auto& s : slopes)
		{
			size_t x = 0;
			size_t y = 0;
			size_t c = 0;
			do
			{
				if (input[y][x] == '#') c++;
				x += s.first;
				y += s.second;
				x %= input[0].size();
			} while (y < input.size());

			m *= c;
		}

		return m;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
