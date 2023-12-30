#include "2023_09.h"

namespace Day09_2023
{
	vector<Data> Main::load(const vector<string>& input)
	{
		vector<Data> v;
		for (const string& s : input)
		{
			v.push_back(Data());
			for (size_t pos, offset = 0; offset < s.size(); offset += pos)
				v.back().push_back(stoll(s.c_str() + offset, &pos));
		}

		return v;
	}

	int64_t Main::extrapolate(Data data, int direction)
	{
		Data values;
		size_t count = data.size();
		while (--count)
		{
			values.push_back(direction == 1 ? data[count] : data[0]);

			bool all_zeroes = true;
			for (size_t i = 0; i < count; i++)
			{
				data[i] = data[i + 1] - data[i];
				if (data[i] != 0)
					all_zeroes = false;
			}

			if (all_zeroes)
				break;
		}

		int64_t v = 0;
		for (Data::const_reverse_iterator it = values.rbegin(); it != values.rend(); it++)
			v = *it + (v * direction);

		return v;
	}

	int64_t Main::solve(const vector<Data>& v, int direction)
	{
		int64_t sum = 0;
		for (const auto& data : v)
			sum += extrapolate(data, direction);

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(load(input), 1);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(load(input), -1);
	}
}
