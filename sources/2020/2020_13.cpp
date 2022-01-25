#include "2020_13.h"

namespace Day13_2020
{
	t_buses Main::load(const vector<string>& input)
	{
		t_buses buses;
		int i = -1;
		string line;
		stringstream ss(input[1]);
		while (getline(ss, line, ','))
		{
			i++;
			if (line != "x")
				buses.push_back(make_pair(stoi(line), i));
		}

		return buses;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int timestamp = stoi(input[0]);
		auto buses = load(input);

		vector<int> dep(buses.size() - 1);
		for (size_t i = 0; i < buses.size() - 1; i++)
		{
			int v = (timestamp / buses[i].first) * buses[i].first;
			if (v < timestamp)
				v += buses[i].first;

			dep[i] = v - timestamp;
		}

		int r = -1;
		int v = INT_MAX;
		for (size_t i = 0; i < dep.size(); i++)
			if (dep[i] < v)
			{
				v = dep[i];
				r = v * buses[i].first;
			}

		return r;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		// note: second part solution strongly relies on primary numbers as buses IDs
		
		auto buses = load(input);

		int64_t t = 0;
		int64_t s = 1;
		for (const auto& b : buses)
		{
			while ((t + b.second) % b.first > 0)
				t += s;

			s *= b.first;
		}

		return t;
	}
}
