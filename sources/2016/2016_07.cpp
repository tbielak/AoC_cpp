#include "2016_07.h"

namespace Day07_2016
{
	bool supports_TLS(const string& s)
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

	bool supports_SSL(const string& s)
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

	int part_one(const t_input& input)
	{
		return (int)count_if(input.begin(), input.end(), [](const auto& s) { return supports_TLS(s); });
	}

	int part_two(const t_input& input)
	{
		return (int)count_if(input.begin(), input.end(), [](const auto& s) { return supports_SSL(s); });
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
