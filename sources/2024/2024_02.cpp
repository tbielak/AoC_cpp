#include "2024_02.h"

namespace Day02_2024
{
	vector<vector<int>> Main::load(const vector<string>& input)
	{
		vector<vector<int>> data;
		for (const auto& s : input)
		{
			data.push_back(vector<int>());
			string v;
			stringstream ss(s);
			while (getline(ss, v, ' '))
				data.back().push_back(stoi(v));
		}

		return data;
	}

	bool Main::is_safe(const vector<int>& v)
	{
		bool inc = v[1] > v[0];
		for (size_t i = 1; i < v.size(); i++)
		{
			if (inc)
			{
				if (v[i] <= v[i-1] || v[i] - v[i-1] > 3)
					return false;
			}
			else
			{
				if (v[i-1] <= v[i] || v[i-1] - v[i] > 3)
					return false;
			}
		}

		return true;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto data = load(input);

		int safe = 0;
		for (const auto& v : data)
			if (is_safe(v))
				safe++;

		return safe;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);

		int safe = 0;
		for (const auto& v : data)
		{
			if (is_safe(v))
				safe++;
			else
			{
				for (size_t i = 0; i < v.size(); i++)
				{
					vector<int> t;
					for (size_t j = 0; j < v.size(); j++)
						if (j != i)
							t.push_back(v[j]);

					if (is_safe(t))
					{
						safe++;
						break;
					}
				}
			}
		}

		return safe;
	}
}
