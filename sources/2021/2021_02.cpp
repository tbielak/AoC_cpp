#include "2021_02.h"

namespace Day02_2021
{
	typedef vector<pair<char, intmax_t>> t_course;

	intmax_t part_one(const t_course& course)
	{
		intmax_t position = 0;
		intmax_t depth = 0;
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

	intmax_t part_two(const t_course& course)
	{
		intmax_t position = 0;
		intmax_t depth = 0;
		intmax_t aim = 0;
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

	t_output main(const t_input& input)
	{
		smatch matches;
		regex regex("(forward|up|down) ([0-9])");
		t_course course;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			course.push_back(make_pair(matches[1].str()[0], stoi(matches[2].str())));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(course);
		auto p2 = part_two(course);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
