#include "2020_02.h"

namespace Day02_2020
{
	Item::Item(int min, int max, char letter, const string& password)
	:	min(min), max(max), letter(letter), password(password)
	{
	}

	int part_one(const vector<Item>& items)
	{
		int c = 0;
		for (const auto& x : items)
		{
			int p = (int)count(x.password.begin(), x.password.end(), x.letter);
			if (p >= x.min && p <= x.max)
				c++;
		}

		return c;
	}

	int part_two(const vector<Item>& items)
	{
		int c = 0;
		for (const auto& x : items)
			if ((x.password[x.min - 1] == x.letter) ^ (x.password[x.max - 1] == x.letter))
				c++;

		return c;
	}

	t_output main(const t_input& input)
	{
		regex regex("([0-9]*)-([0-9]*) ([a-z]): (.*)");
		smatch matches;
		vector<Item> items;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			items.push_back(Item(stoi(matches[1].str()), stoi(matches[2].str()), matches[3].str()[0], matches[4].str()));
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
