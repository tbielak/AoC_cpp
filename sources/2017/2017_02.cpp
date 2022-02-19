#include "2017_02.h"

namespace Day02_2017
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& s : input)
		{
			int number;
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

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto data = load(input);

		int sum = 0;
		for (const auto& row : data)
			sum += *max_element(row.begin(), row.end()) - *min_element(row.begin(), row.end());

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);

		int sum = 0;
		for (const auto& row : data)
		{
			for (int i = 0; i < (int)row.size(); i++)
				for (int j = i + 1; j < (int)row.size(); j++)
				{
					int a = row[i];
					int b = row[j];
					if (a < b)
						swap(a, b);

					if ((a % b) == 0)
					{
						sum += a / b;
						break;
					}
				}

		}

		return sum;
	}
}
