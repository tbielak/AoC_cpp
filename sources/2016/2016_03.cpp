#include "2016_03.h"

namespace Day03_2016
{
	t_data Main::load(const vector<string>& input)
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

		return data;
	}

	bool Main::is_triangle(vector<int> x)
	{
		sort(x.begin(), x.end());
		return x[0] + x[1] > x[2];
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_data data = load(input);

		return (int)count_if(data.begin(), data.end(), [](const auto& v) { return is_triangle(v); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_data data = load(input);

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
}
