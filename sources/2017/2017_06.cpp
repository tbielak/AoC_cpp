#include "2017_06.h"

namespace Day06_2017
{
	t_data Main::load(const string& input)
	{
		t_data data;
		stringstream ss(input);

		int number;
		while (ss >> number)
		{
			data.push_back(number);
			ss.ignore(1);
		}

		return data;
	}

	pair<int, t_data> Main::solve(const string& input, const t_data& observe /* = t_data() */)
	{
		auto data = load(input);
		bool counting = (observe.size() == 0);
		int step = 0;
		t_known known;
		known.insert(data);

		while (1)
		{
			if (counting)
				step++;

			int max_idx = 0;
			int max_value = 0;
			for (int i = 0; i < (int)data.size(); i++)
				if (data[i] > max_value)
				{
					max_value = data[i];
					max_idx = i;
				}

			data[max_idx] = 0;
			max_idx = (max_idx + 1) % (int)data.size();

			for (int i = 0; i < max_value; i++)
			{
				data[max_idx]++;
				max_idx = (max_idx + 1) % (int)data.size();
			}

			if (!counting && data == observe)
				counting = true;

			t_known::const_iterator it = known.find(data);
			if (it != known.end())
				return make_pair(step, data);

			known.insert(data);
		}

		return make_pair(-1, t_data());
	}

	AoC::Output Main::part_one(const string& input)
	{
		auto result = solve(input);
		_observe = result.second;
		return result.first;
	}

	AoC::Output Main::part_two(const string& input)
	{
		return solve(input, _observe).first;
	}
}
