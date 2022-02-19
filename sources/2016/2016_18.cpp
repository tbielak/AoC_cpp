#include "2016_18.h"

namespace Day18_2016
{
	int Main::count_safe(const string& input, int rows)
	{
		vector<string> room;
		room.push_back(input);

		for (int j = 0; j < rows - 1; j++)
		{
			string prev = "." + room[j] + ".";
			string next(room[j].size(), '.');
			for (int i = 0; i < (int)next.size(); i++)
			{
				string part = prev.substr(i, 3);
				if (part == "^^." || part == ".^^" || part == "^.." || part == "..^")
					next[i] = '^';
			}

			room.push_back(next);
		}

		int count = 0;
		for (const auto r : room)
			count += (int)count_if(r.begin(), r.end(), [](char c) { return c == '.';  });

		return count;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return count_safe(input, 40);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return count_safe(input, 400000);
	}
}
