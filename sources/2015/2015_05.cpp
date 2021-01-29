#include "2015_05.h"

namespace Day05_2015
{
	bool nice_part_one(const string& s)
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

	bool nice_part_two(const string& s)
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

	int part_one(const vector<string>& x)
	{
		return (int)count_if(x.begin(), x.end(), [](auto s) { return nice_part_one(s); });
	}

	int part_two(const vector<string>& x)
	{
		return (int)count_if(x.begin(), x.end(), [](auto s) { return nice_part_two(s); });
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
