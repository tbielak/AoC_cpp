#include "2023_01.h"

namespace Day01_2023
{
	vector<string> Main::_empty = {};
	vector<string> Main::_fdigits = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	vector<string> Main::_rdigits = { "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin" };

	int Main::digit(const string& s, const vector<string>& words)
	{
		size_t d = 0;
		for (; d < s.size(); d++)
			if (isdigit(s[d]))
				break;

		if (!words.empty())
			for (size_t i = 0; i < d; i++)
				for (size_t j = 0; j < words.size(); j++)
					if (s.substr(i, words[j].size()) == words[j])
						return int(j + 1);

		return s[d] - '0';
	}

	int Main::sum(const vector<string>& input, const vector<string>& fwd, const vector<string>& rev)
	{
		int sum = 0;
		for (const string& s : input)
			sum += digit(s, fwd) * 10 + digit(string(s.rbegin(), s.rend()), rev);

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return sum(input, _empty, _empty);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return sum(input, _fdigits, _rdigits);
	}
}
