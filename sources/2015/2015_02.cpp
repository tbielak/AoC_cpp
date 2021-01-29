#include "2015_02.h"

namespace Day02_2015
{
	int part_one(const t_items& items)
	{
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

	int part_two(const t_items& items)
	{
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

	t_output main(const t_input& input)
	{
		smatch matches;
		regex regex("([0-9]*)x([0-9]*)x([0-9]*)");
		t_items items;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			items.push_back(make_tuple(stoi(matches[1].str()), stoi(matches[2].str()), stoi(matches[3].str())));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(items);
		auto p2 = part_two(items);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
