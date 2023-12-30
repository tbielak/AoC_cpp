#include "2023_12.h"

namespace Day12_2023
{
	int64_t Main::solve(Area& area, const string& s, vector<int> v, int i, int j, int c)
	{
		if (i >= (int)s.size())
			return j == (int)v.size() ? 1 : 0;

		int64_t& result = area[i][j][c];
		if (result != -1)
			return result;

		result++;
		if ((s[i] == '.' || s[i] == '?') && c == 0)
			result += solve(area, s, v, i + 1, j, 0);

		if (j < (int)v.size())
		{
			if (s[i] == '#' || s[i] == '?')
			{
				if (v[j] == c + 1)
				{
					if (i + 1 == (int)s.size() || s[i + 1] != '#')
						result += solve(area, s, v, i + 2, j + 1, 0);
				}
				else
					result += solve(area, s, v, i + 1, j, c + 1);
			}
		}

		return result;
	}

	int64_t Main::solve(const string& input, int rep)
	{
		size_t pos = input.find_first_of(' ');
		string s = input.substr(0, pos);

		int max_v = 0;
		vector<int> v;
		for (size_t offset = pos + 1; offset < input.size(); offset += pos + 1)
		{
			int x = stoi(input.c_str() + offset, &pos);
			v.push_back(x);
			max_v = max(max_v, x);
		}

		string ss = s;
		for (int i = 0; i < rep - 1; i++)
			ss += "?" + s;

		vector<int> vv = v;
		for (int i = 0; i < rep - 1; i++)
			for (auto x : v)
				vv.push_back(x);

		Area area(ss.size(), vector<vector<int64_t>>(vv.size() + 1, vector<int64_t>(max_v, -1)));
		return solve(area, ss, vv, 0, 0, 0);
	}

	int64_t Main::solve(const vector<string>& input, int rep)
	{
		int64_t sum = 0;
		for (const auto& s : input)
			sum += solve(s, rep);

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, 1);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 5);
	}
}
