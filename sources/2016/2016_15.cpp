#include "2016_15.h"

namespace Day15_2016
{
	t_discs Main::load(const vector<string>& input)
	{
		t_discs discs;
		for (const auto& s : input)
		{
			smatch matches;
			regex regex("Disc #([0-9]*) has ([0-9]*) positions; at time=0, it is at position ([0-9]*).");
			regex_search(s, matches, regex);
			discs.push_back(make_pair(stoi(matches[3]), stoi(matches[2])));
		}

		return discs;
	}

	int Main::solve(const t_discs& discs)
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

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_discs discs = load(input);
		return solve(discs);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_discs discs = load(input);
		discs.push_back(make_pair(0, 11));
		return solve(discs);
	}
}
