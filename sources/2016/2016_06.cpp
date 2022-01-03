#include "2016_06.h"

namespace Day06_2016
{
	pair<string, string> both_parts(const t_input& input)
	{
		// message length
		int length = (int)input[0].size();

		// number of different characters for each position
		vector<map<char, int>> count(length, map<char, int>());
		for (const auto& s : input)
			for (int i = 0; i < length; i++)
				count[i][s[i]]++;

		// get result
		string most_common, least_common;
		auto comparator = [](const auto& a, const auto& b) -> int { return a.second < b.second; };
		for (const auto& c : count)
		{
			most_common += max_element(c.begin(), c.end(), comparator)->first;
			least_common += min_element(c.begin(), c.end(), comparator)->first;
		}

		return make_pair(most_common, least_common);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(px.first);
		solutions.push_back(px.second);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
