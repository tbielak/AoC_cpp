#include "2018_05.h"

namespace Day05_2018
{
	bool Main::keep(char a, char b)
	{
		if (a == b)
			return true;

		return (tolower(a) != tolower(b));
	}

	size_t Main::react_length(const string& input, char skip /* = 0 */)
	{
		stack<char> s;
		for (auto c : input)
		{
			if (s.size() == 0 || keep(s.top(), c))
			{
				if (tolower(c) != tolower(skip))
					s.push(c);
			}
			else
				s.pop();
		}

		return s.size();
	}

	AoC::Output Main::part_one(const string& input)
	{
		return react_length(input);
	}

	AoC::Output Main::part_two(const string& input)
	{
		size_t m = input.size();
		for (char c = 'a'; c <= 'z'; c++)
		{
			size_t length = react_length(input, c);
			if (m > length)
				m = length;
		}

		return m;
	}
}
