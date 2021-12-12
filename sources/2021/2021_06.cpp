#include "2021_06.h"

namespace Day06_2021
{
	intmax_t number_of_elements(int x, int days)
	{
		vector<intmax_t> count = vector<intmax_t>(9, 0);
		count[x]++;

		intmax_t v = 0;
		for (int d = 0; d < days; d++)
		{
			v = count[0];
			for (int i = 0; i < 8; i++)
				count[i] = count[i + 1];

			count[6] += v;
			count[8] = v;
		}

		intmax_t sum = 0;
		for (auto n : count)
			sum += n;

		return sum;
	}

	intmax_t lanternfish_count(const vector<int>& x, int days)
	{
		int m = *max_element(x.begin(), x.end()) + 1;
		vector<intmax_t> counts = vector<intmax_t>(m);
		for (int i = 0; i < m; i++)
			counts[i] = number_of_elements(i, days);

		intmax_t sum = 0;
		for (auto n : x)
			sum += counts[n];

		return sum;
	}

	intmax_t part_one(const vector<int>& x)
	{
		return lanternfish_count(x, 80);
	}

	intmax_t part_two(const vector<int>& x)
	{
		return lanternfish_count(x, 256);
	}

	t_output main(const t_input& input)
	{
		vector<int> x;
		int number;
		stringstream ss(input[0]);
		while (ss >> number)
		{
			x.push_back(number);
			ss.ignore(1);
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(x);
		auto p2 = part_two(x);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
