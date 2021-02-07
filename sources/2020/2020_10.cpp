#include "2020_10.h"

namespace Day10_2020
{
	int part_one(const t_data& data)
	{
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

	uintmax_t part_two(const t_data& data)
	{
		t_data p = data;
		p.push_back(0);
		sort(p.begin(), p.end());

		vector<uintmax_t> s(p.size());
		s[0] = 1;

		for (size_t i = 1; i < p.size(); i++)
		{
			uintmax_t sum = 0;
			for (size_t j = 1; j <= 3; j++)
				if (i > j - 1 && p[i] - p[i - j] <= 3)
					sum += s[i - j];

			s[i] = sum;
		}

		return s.back();
	}

	t_output main(const t_input& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoi(line));

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(data);
		auto p2 = part_two(data);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
