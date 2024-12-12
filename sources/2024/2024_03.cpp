#include "2024_03.h"

namespace Day03_2024
{
	bool Main::get_number(const string& s, int& left, size_t& pos)
	{
		left = 0;
		if (pos == s.size() || !isdigit(s[pos]))
			return false;
		
		while (pos < s.size() && isdigit(s[pos]))
			left = 10 * left + s[pos++] - '0';

		return true;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int left, right;
		int64_t sum = 0;
		for (const auto& s : input)
		{
			size_t pos = 0;
			while (1)
			{
				pos = s.find("mul(", pos);
				if (pos == string::npos)
					break;

				pos += 4;
				if (!get_number(s, left, pos))
					continue;

				if (pos == s.size() || s[pos++] != ',')
					continue;

				if (!get_number(s, right, pos))
					continue;

				if (pos == s.size() || s[pos++] != ')')
					continue;

				sum += left * right;
			}
		}

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		bool enabled = true;
		int left, right;
		int64_t sum = 0;
		for (const auto& s : input)
		{
			size_t pos = 0;
			while (1)
			{
				size_t ctrl = enabled ? s.find("don't()", pos) : s.find("do()", pos);
				pos = s.find("mul(", pos);
				if (pos == string::npos)
					break;

				if (ctrl < pos)
					enabled = !enabled;

				pos += 4;
				if (!enabled)
					continue;

				if (!get_number(s, left, pos))
					continue;

				if (pos == s.size() || s[pos++] != ',')
					continue;

				if (!get_number(s, right, pos))
					continue;

				if (pos == s.size() || s[pos++] != ')')
					continue;

				sum += left * right;
			}
		}

		return sum;
	}
}
