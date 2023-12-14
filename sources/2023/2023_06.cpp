#include "2023_06.h"

namespace Day06_2023
{
	Data Main::load(const string& s, char after)
	{
		Data v;
		size_t pos;
		for (size_t offset = s.find_first_of(after) + 1; offset < s.size(); offset += pos)
			v.push_back(stoll(s.c_str() + offset, &pos));

		return v;
	}

	string Main::remove_spaces(const string& s)
	{
		string v;
		for (char c : s)
			if (c != ' ')
				v += c;

		return v;
	}

	int64_t Main::solve(const Data& time, const Data& record)
	{
		int64_t result = 1;
		for (size_t i = 0; i < time.size(); i++)
		{
			int64_t ways = 0;
			for (int pressed = 0; pressed < time[i]; pressed++)
			{
				int64_t distance = (time[i] - pressed) * pressed;
				if (distance > record[i])
					ways++;
			}

			result *= ways;
		}

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto time = load(input[0], ':');
		auto record = load(input[1], ':');
		return solve(time, record);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto time = load(remove_spaces(input[0]), ':');
		auto record = load(remove_spaces(input[1]), ':');
		return solve(time, record);
	}
}
