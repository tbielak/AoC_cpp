#include "2016_15.h"

namespace Day15_2016
{
	int solve(const t_discs& discs)
	{
		int time = 0;
		int step = 1;
		int offset = 0;

		for (const auto& d : discs)
		{
			auto [curpos, maxpos] = d;
			curpos += ++offset + time % maxpos;
			curpos %= maxpos;

			while (curpos != 0)
			{
				time += step;
				curpos += step;
				curpos %= maxpos;
			}

			step *= maxpos;
		}

		return time;
	}

	int part_one(const t_discs& discs)
	{
		return solve(discs);
	}

	int part_two(t_discs& discs)
	{
		discs.push_back(make_pair(0, 11));
		return solve(discs);
	}

	t_output main(const t_input& input)
	{
		t_discs discs;
		for (const auto& s : input)
		{
			smatch matches;
			regex regex("Disc #([0-9]*) has ([0-9]*) positions; at time=0, it is at position ([0-9]*).");
			regex_search(s, matches, regex);
			discs.push_back(make_pair(stoi(matches[3]), stoi(matches[2])));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(discs);
		auto p2 = part_two(discs);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
