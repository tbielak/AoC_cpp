#include "2020_10.h"

namespace Day10_2020
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoi(line));

		return data;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto data = load(input);

		int devja = -1;
		for (auto& v : data)
			devja = max(devja, v);

		devja += 3;
		t_data d(devja + 1);
		for (auto& v : data)
			d[v] = 1;

		int d1 = 1;
		for (size_t i = 1; i < d.size() - 1; i++)
			if (d[i] == 1 && d[i + 1] == 1)
				d1++;

		int d3 = 1;
		for (size_t i = 1; i < d.size() - 3; i++)
			if (d[i] == 1 && d[i + 1] == 0 && d[i + 2] == 0 && d[i + 3] == 1)
				d3++;

		return d1 * d3;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);
	
		t_data p = data;
		p.push_back(0);
		sort(p.begin(), p.end());

		vector<int64_t> s(p.size());
		s[0] = 1;

		for (size_t i = 1; i < p.size(); i++)
		{
			int64_t sum = 0;
			for (size_t j = 1; j <= 3; j++)
				if (i > j - 1 && p[i] - p[i - j] <= 3)
					sum += s[i - j];

			s[i] = sum;
		}

		return s.back();
	}
}
