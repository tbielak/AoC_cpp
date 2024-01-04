#include "2023_13.h"

namespace Day13_2023
{
	vector<Pattern> Main::load(const vector<string>& input)
	{
		vector<Pattern> v = vector<Pattern>(1);
		for (const string& s : input)
		{
			if (s.empty())
				v.push_back(Pattern());
			else
				v.back().push_back(s);
		}

		return v;
	}

	Pattern Main::rotate(const Pattern& src)
	{
		Pattern dst = vector<string>(src[0].size(), string(src.size(), ' '));
		for (size_t y = 0; y < src.size(); y++)
			for (size_t x = 0; x < src[y].size(); x++)
				dst[x][y] = src[y][x];

		return dst;
	}

	bool Main::check_diffs(const Pattern& p, int k, int smudges)
	{
		int d = 0;
		for (int i = k - 1, j = k; d <= smudges && i >= 0 && j < (int)p.size(); i--, j++)
			for (int m = 0; m < (int)p[0].size(); m++)
				d += p[i][m] != p[j][m];

		return d == smudges;
	}

	int Main::find_reflection(const Pattern& p, int smudges)
	{
		for (int k = 1; k < (int)p.size(); k++)
			if (check_diffs(p, k, smudges))
				return k;

		return 0;
	}

	int Main::solve(const vector<string>& input, int smudges)
	{
		int sum = 0;
		for (const auto& p : load(input))
			sum += find_reflection(p, smudges) * 100 + find_reflection(rotate(p), smudges);

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, 0);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 1);
	}
}
