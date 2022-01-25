#include "2021_02.h"

namespace Day02_2021
{
	t_course Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("(forward|up|down) ([0-9])");
		t_course course;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			course.push_back(make_pair(matches[1].str()[0], stoi(matches[2].str())));
		}

		return course;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto course = load(input);

		int64_t position = 0;
		int64_t depth = 0;
		for (const auto& c : course)
		{
			switch (c.first)
			{
				case 'd': depth += c.second; break;
				case 'u': depth -= c.second; break;
				default: position += c.second; break;
			}
		}

		return position * depth;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto course = load(input);

		int64_t position = 0;
		int64_t depth = 0;
		int64_t aim = 0;
		for (const auto& c : course)
		{
			switch (c.first)
			{
				case 'd': aim += c.second; break;
				case 'u': aim -= c.second; break;
				default:
				{
					position += c.second;
					depth += aim * c.second;
					break;
				}
			}
		}

		return position * depth;
	}
}
