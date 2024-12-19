#include "2024_19.h"

namespace Day19_2024
{
	pair <vector<string>, vector<string>> Main::load(const vector<string>& input)
	{
		vector<string> patterns, designs;

		string v;
		stringstream ss(input[0]);
		while (getline(ss, v, ','))
			patterns.push_back(v[0] == ' ' ? v.substr(1) : v);

		for (size_t i = 2; i < input.size(); i++)
			designs.push_back(input[i]);

		return make_pair(patterns, designs);
	}

	int64_t Main::count(const vector<string>& patterns, const string& design)
	{
		vector<int64_t> sum(design.size() + 1, 0);
		sum[0] = 1;

		for (size_t i = 1; i <= design.size(); i++)
			for (const string& p : patterns)
			{
				size_t len = p.size();
				if (i >= len && design.substr(i - len, len) == p)
					sum[i] += sum[i - len];
			}

		return sum[design.size()];
	}

	vector<int64_t> Main::count(const vector<string>& patterns, const vector<string>& designs)
	{
		vector<int64_t> ways;
		for (const string& d : designs)
			ways.push_back(count(patterns, d));
		
		return ways;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		auto [patterns, designs] = load(input);
		auto ways = count(patterns, designs);

		int64_t possible = 0;
		int64_t different_ways = 0;
		for (auto w : ways)
		{
			if (w > 0)
				possible++;

			different_ways += w;
		}

		return make_pair(possible, different_ways);
	}
}
