#include "2015_05.h"

namespace Day05_2015
{
	bool Main::nice_part_one(const string& s)
	{
		// [1]
		int c = 0;
		const string vowels = "aeiou";
		for (auto ch : s)
			if (vowels.find(ch) != string::npos)
				c++;

		if (c < 3)
			return false;

		// [2]
		c = 0;
		for (size_t i = 0; i < s.size() - 1; i++)
			if (s[i] == s[i + 1])
			{
				c++;
				break;
			}

		if (0 == c)
			return false;

		// [3]
		if (s.find("ab") != string::npos || s.find("cd") != string::npos ||
			s.find("pq") != string::npos || s.find("xy") != string::npos)
			return false;

		return true;
	}

	bool Main::nice_part_two(const string& s)
	{
		// [1]
		bool nice = false;
		for (size_t i = 0; i < s.size() - 1; i++)
			for (size_t j = i + 2; j < s.size() - 1; j++)
				if (s[i] == s[j] && s[i + 1] == s[j + 1])
				{
					nice = true;
					break;
				}

		if (!nice)
			return false;

		// [2]
		nice = false;
		for (size_t i = 1; i < s.size() - 1; i++)
			if (s[i - 1] == s[i + 1])
			{
				nice = true;
				break;
			}

		return nice;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return (int)count_if(input.begin(), input.end(), [this](const string& s) { return nice_part_one(s); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return (int)count_if(input.begin(), input.end(), [this](const string& s) { return nice_part_two(s); });
	}
}
