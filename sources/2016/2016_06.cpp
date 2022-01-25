#include "2016_06.h"

namespace Day06_2016
{
	AoC::Output Main::both_parts(const vector<string>& input)
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
}
