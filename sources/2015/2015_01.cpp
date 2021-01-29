#include "2015_01.h"

namespace Day01_2015
{
	int part_one(const string& s)
	{
		return (int)(count(s.begin(), s.end(), '(') - count(s.begin(), s.end(), ')'));
	}

	int part_two(const string& s)
	{
		int c = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			if ('(' == s[i]) c++;
			if (')' == s[i]) c--;
			if (-1 == c)
				return int(i) + 1;
		}

		return -1;
	}

	t_output main(const t_input& input)
	{
		string line = input[0];
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(line);
		auto p2 = part_two(line);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
