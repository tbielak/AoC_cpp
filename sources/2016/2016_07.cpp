#include "2016_07.h"

namespace Day07_2016
{
	bool Main::supports_TLS(const string& s)
	{
		bool abba = false;
		bool bracket = false;
		for (size_t i = 0; i <= s.size() - 4; i++)
		{
			if (s[i] == '[')
				bracket = true;
			else
				if (s[i] == ']')
					bracket = false;
				else
					if (s[i] == s[i + 3] && s[i + 1] == s[i + 2] && s[i] != s[i + 1])
					{
						if (bracket)
						{
							abba = false;
							break;
						}
						else
							abba = true;
					}
		}

		return abba;
	}

	bool Main::supports_SSL(const string& s)
	{
		bool bracket = false;
		set<pair<char, char>> aba, bab;
		for (size_t i = 0; i <= s.size() - 3; i++)
		{
			if (s[i] == '[')
				bracket = true;
			else
				if (s[i] == ']')
					bracket = false;
				else
					if (s[i] == s[i + 2] && s[i] != s[i + 1])
					{
						if (bracket)
							bab.insert(make_pair(s[i + 1], s[i]));
						else
							aba.insert(make_pair(s[i], s[i + 1]));
					}
		}

		for (const auto& x : aba)
			if (bab.find(x) != bab.end())
				return true;

		return false;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return (int)count_if(input.begin(), input.end(), [](const auto& s) { return supports_TLS(s); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return (int)count_if(input.begin(), input.end(), [](const auto& s) { return supports_SSL(s); });
	}
}
