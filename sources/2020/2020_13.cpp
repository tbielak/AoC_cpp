#include "2020_13.h"

namespace Day13_2020
{
	int part_one(int timestamp, const t_buses& buses)
	{
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

	uintmax_t part_two(const t_buses& buses)
	{
		// note: second part solution strongly relies on primary numbers as buses IDs

		uintmax_t t = 0;
		uintmax_t s = 1;
		for (const auto& b : buses)
		{
			while ((t + b.second) % b.first > 0)
				t += s;

			s *= b.first;
		}

		return t;
	}

	t_output main(const t_input& input)
	{
		int timestamp = stoi(input[0]);

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

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(timestamp, buses);
		auto p2 = part_two(buses);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
