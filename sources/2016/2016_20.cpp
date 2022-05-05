#include "2016_20.h"

namespace Day20_2016
{
	// block range on white_list
	void Main::block(t_vecrange& white_list, const t_range& range)
	{
		for (int i = 0; i < (int)white_list.size(); i++)
		{
			t_range& white = white_list[i];

			// range outside white
			if (range.second < white.first || range.first > white.second)
				continue;

			// range inside white -> split white to two elements
			if (range.first > white.first && range.second < white.second)
			{
				t_range tmp = make_pair(white.first, range.first - 1);
				white_list[i] = make_pair(range.second + 1, white.second);
				white_list.insert(white_list.begin() + i, tmp);
				continue;
			}

			// range covers whole white -> remove white
			if (range.first <= white.first && range.second >= white.second)
			{
				white_list.erase(white_list.begin() + i);
				i--;
				continue;
			}

			// range covers left side of white -> update white.first
			if (range.first <= white.first)
				white.first = range.second + 1;
			else
				// range covers right side of white -> update white.second
				if (range.second >= white.second)
					white.second = range.first - 1;
		}
	}

	t_vecrange Main::load(const vector<string>& input)
	{
		// white list allowing all IPs
		t_vecrange white_list;
		white_list.push_back(make_pair(0, 0xffffffff));

		for (const auto& s : input)
		{
			// block IP range
			size_t pos = s.find_first_of("-");
			block(white_list, make_pair(stoul(s.substr(0, pos)), stoul(s.substr(pos + 1))));
		}

		return white_list;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto white_list = load(input);
		return white_list[0].first;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto white_list = load(input);
		return accumulate(white_list.begin(), white_list.end(), 0,
			[](uint32_t sum, const t_range& range) { return sum + range.second - range.first + 1; });
	}
}
