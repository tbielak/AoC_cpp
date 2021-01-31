#include "2015_08.h"

namespace Day08_2015
{
	size_t count_chars(const string& s)
	{
		size_t c = 0;
		for (size_t i = 1; i < s.size() - 1; i++, c++)
			if ('\\' == s[i])
			{
				i++;
				if ('x' == s[i])
					i += 2;
			}

		return c;
	}

	int encoded_length(const string& s)
	{
		int c = 2;
		for (auto v : s)
			c += int('"' == v || '\\' == v) + 1;

		return c;
	}

	size_t part_one(const vector<string>& input, size_t& bytes)
	{
		size_t chars = 0;
		bytes = 0;
		for (const auto& s : input)
		{
			chars += count_chars(s);
			bytes += s.size();
		}

		return bytes - chars;
	}

	size_t part_two(const vector<string>& input, size_t bytes)
	{
		return (size_t)accumulate(input.begin(), input.end(), 0,
			[](int sum, const string& s) { return sum + encoded_length(s); }) - bytes;
	}

	t_output main(const t_input& input)
	{
		size_t bytes = 0;
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input, bytes);
		auto p2 = part_two(input, bytes);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
