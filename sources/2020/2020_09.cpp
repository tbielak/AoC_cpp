#include "2020_09.h"

namespace Day09_2020
{
	bool valid(const t_data& data, uintmax_t n)
	{
		for (size_t i = n - preamble; i < n; i++)
			for (size_t j = i + 1; j < n; j++)
				if (data[i] + data[j] == data[n])
					return true;

		return false;
	}

	uintmax_t part_one(const t_data& data)
	{
		for (size_t i = preamble; i < data.size(); i++)
			if (!valid(data, i))
				return data[i];

		return 0;
	}

	uintmax_t part_two(const t_data& data, uintmax_t v)
	{
		for (size_t i = 0; i < data.size() - 1; i++)
			for (size_t j = i + 1; j < data.size(); j++)
			{
				uintmax_t sum = 0;
				for (size_t k = i; k <= j; k++)
					sum += data[k];

				if (sum == v)
				{
					uintmax_t dmin = ULLONG_MAX;
					uintmax_t dmax = 0;
					for (size_t k = i; k <= j; k++)
					{
						dmin = min(dmin, data[k]);
						dmax = max(dmax, data[k]);
					}

					return dmin + dmax;
				}
			}

		return 0;
	}

	t_output main(const t_input& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoll(line));

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(data);
		auto p2 = part_two(data, p1);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
