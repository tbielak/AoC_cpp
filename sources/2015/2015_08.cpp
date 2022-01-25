#include "2015_08.h"

namespace Day08_2015
{
	Main::Main()
	:	_bytes(0)
	{
	}

	int Main::count_chars(const string& s)
	{
		int c = 0;
		for (int i = 1; i < (int)s.size() - 1; i++, c++)
			if ('\\' == s[i])
			{
				i++;
				if ('x' == s[i])
					i += 2;
			}

		return c;
	}

	int Main::encoded_length(const string& s)
	{
		int c = 2;
		for (auto v : s)
			c += int('"' == v || '\\' == v) + 1;

		return c;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int chars = 0;
		_bytes = 0;
		for (const auto& s : input)
		{
			chars += count_chars(s);
			_bytes += (int)s.size();
		}

		return _bytes - chars;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return (int64_t)accumulate(input.begin(), input.end(), 0,
			[this](int sum, const string& s) { return sum + encoded_length(s); }) - _bytes;
	}
}
