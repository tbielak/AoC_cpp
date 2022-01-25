#include "2020_09.h"

namespace Day09_2020
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoll(line));

		return data;
	}

	bool Main::valid(const t_data& data, int64_t n)
	{
		for (int64_t i = n - preamble; i < n; i++)
			for (int64_t j = i + 1; j < n; j++)
				if (data[i] + data[j] == data[n])
					return true;

		return false;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto data = load(input);

		for (size_t i = preamble; i < data.size(); i++)
			if (!valid(data, i))
				return data[i];

		return 0;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);

		int64_t v = 0;
		for (size_t i = preamble; i < data.size(); i++)
			if (!valid(data, i))
			{
				v = data[i];
				break;
			}

		for (size_t i = 0; i < data.size() - 1; i++)
			for (size_t j = i + 1; j < data.size(); j++)
			{
				int64_t sum = 0;
				for (size_t k = i; k <= j; k++)
					sum += data[k];

				if (sum == v)
				{
					int64_t dmin = LLONG_MAX;
					int64_t dmax = 0;
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
}
