#include "2017_15.h"

namespace Day15_2017
{
	pair<int64_t, int64_t> Main::load(const vector<string>& input)
	{
		int64_t A = 0;
		int64_t B = 0;

		smatch matches;
		regex regex("Generator (A|B) starts with ([0-9]*)");
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			if (matches[1] == 'A')
				A = stoi(matches[2]);
			if (matches[1] == 'B')
				B = stoi(matches[2]);
		}

		return make_pair(A, B);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [A, B] = load(input);

		int count = 0;
		for (int i = 0; i < 40000000; i++)
		{
			A = (A * 16807) % 2147483647;
			B = (B * 48271) % 2147483647;
			if ((A & 0xffff) == (B & 0xffff))
				count++;
		}

		return count;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [A, B] = load(input);

		int count = 0;
		for (int i = 0; i < 5000000; i++)
		{
			do A = (A * 16807) % 2147483647; while ((A % 4) > 0);
			do B = (B * 48271) % 2147483647; while ((B % 8) > 0);
			if ((A & 0xffff) == (B & 0xffff))
				count++;
		}

		return count;
	}
}
