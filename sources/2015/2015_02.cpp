#include "2015_02.h"

namespace Day02_2015
{
	t_items Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("([0-9]*)x([0-9]*)x([0-9]*)");
		t_items items;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			items.push_back(make_tuple(stoi(matches[1].str()), stoi(matches[2].str()), stoi(matches[3].str())));
		}

		return items;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_items items = load(input);

		int area = 0;
		vector<int> s(3);
		for (const auto& x : items)
		{
			const auto& [l, w, h] = x;
			s[0] = l * w;
			s[1] = w * h;
			s[2] = h * l;
			sort(s.begin(), s.end());
			area += accumulate(s.begin(), s.end(), 0) * 2 + s[0];
		}

		return area;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_items items = load(input);

		int ribbon = 0;
		vector<int> s(3);
		for (const auto& x : items)
		{
			const auto& [l, w, h] = x;
			s[0] = l;
			s[1] = w;
			s[2] = h;
			sort(s.begin(), s.end());
			ribbon += 2 * s[0] + 2 * s[1] + s[0] * s[1] * s[2];
		}

		return ribbon;
	}
}
