#include "2018_02.h"

namespace Day02_2018
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		int two = 0;
		int three = 0;
		for (const auto& s : input)
		{
			map<char, int> charcount;
			for (auto c : s)
				charcount[c]++;

			int add_two = 0;
			int add_three = 0;
			for (const auto& [c, count] : charcount)
			{
				if (count == 2)
					add_two = 1;

				if (count == 3)
					add_three = 1;
			}

			two += add_two;
			three += add_three;
		}

		return two * three;
	}

	string Main::diff(const string& s1, const string& s2)
	{
		string x;
		for (int i = 0; i < (int)s1.size(); i++)
			if (s1[i] == s2[i])
				x += s1[i];

		return x;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		for (size_t i = 0; i < input.size(); i++)
			for (size_t j = i + 1; j < input.size(); j++)
			{
				string x = diff(input[i], input[j]);
				if (x.size() == input[i].size() - 1)
					return x;
			}

		return string("?");	// unreachable code
	}
}
