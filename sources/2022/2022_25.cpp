#include "2022_25.h"

namespace Day25_2022
{
	int64_t Main::SNAFU_to_dec(const string& s)
	{
		static map<char, int> to_dec = { {'2', 2}, {'1', 1}, {'0', 0}, {'-', -1}, {'=', -2} };
		int64_t v = 0;
		for (char c : s)
			v = 5 * v + to_dec[c];

		return v;
	}

	string Main::dec_to_SNAFU(int64_t v)
	{
		string s;
		static string output = "=-012";
		while (v != 0)
		{
			int64_t r = v % 5;
			v /= 5;
			if (r >= 3)
			{
				r -= 5;
				v++;
			}

			s = output[r + 2] + s;
		}

		return s;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int64_t v = 0;
		for (const auto& s : input)
			v += SNAFU_to_dec(s);

		return dec_to_SNAFU(v);
	}
}
