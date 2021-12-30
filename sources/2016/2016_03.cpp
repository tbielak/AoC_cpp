#include "2016_03.h"

namespace Day03_2016
{
	bool is_triangle(vector<int> x)
	{
		sort(x.begin(), x.end());
		return x[0] + x[1] > x[2];
	}

	int part_one(const t_data& data)
	{
		return (int)count_if(data.begin(), data.end(), [](const auto& v) { return is_triangle(v); });
	}

	int part_two(const t_data& data)
	{
		int count = 0;
		int col_sets = int(data.size() / 3);
		for (int i = 0; i < col_sets; i++)
			for (int j = 0; j < 3; j++)
			{
				vector<int> v = vector<int>(3);
				for (int k = 0; k < 3; k++)
					v[k] = data[i * 3 + k][j];

				if (is_triangle(v))
					count++;
			}

		return count;
	}

	t_output main(const t_input& input)
	{
		int number;
		t_data data;

		for (const auto& s : input)
		{
			data.push_back(vector<int>());
			stringstream ss(s);
			while (ss >> number)
			{
				data.back().push_back(number);
				ss.ignore(1);
			}
		}

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
