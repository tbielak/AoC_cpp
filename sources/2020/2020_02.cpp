#include "2020_02.h"

namespace Day02_2020
{
	Item::Item(int min, int max, char letter, const string& password)
	:	min(min), max(max), letter(letter), password(password)
	{
	}

	t_items Main::load(const vector<string>& input)
	{
		t_items items;
		regex regex("([0-9]*)-([0-9]*) ([a-z]): (.*)");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			items.push_back(Item(stoi(matches[1].str()), stoi(matches[2].str()), matches[3].str()[0], matches[4].str()));
		}

		return items;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto items = load(input);

		int c = 0;
		for (const auto& x : items)
		{
			int p = (int)count(x.password.begin(), x.password.end(), x.letter);
			if (p >= x.min && p <= x.max)
				c++;
		}

		return c;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto items = load(input);

		int c = 0;
		for (const auto& x : items)
			if ((x.password[x.min - 1] == x.letter) ^ (x.password[x.max - 1] == x.letter))
				c++;

		return c;
	}
}
