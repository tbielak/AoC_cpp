#include "2020_07.h"

namespace Day07_2020
{
	Luggage::Luggage(const vector<string>& input)
	{
		size_t idx = 0;
		_inside = vector<vector<t_bag>>(input.size());
		for (const auto& s : input)
		{
			const string key = " bags contain ";
			size_t pos = s.find(key);
			_bags[s.substr(0, pos)] = idx++;
			if (s.find("no other bags") != string::npos)
				continue;

			auto in = s.substr(pos + key.size());
			while (in.size() > 0)
			{
				int cnt = in[0] - '0';
				size_t pos = in.find("bag");
				string color = in.substr(2, pos - 3);
				while (pos < in.size() && in[pos] != ' ') pos++;
				in = (pos == in.size()) ? "" : in.substr(pos + 1);
				_inside[idx - 1].push_back(make_pair(color, cnt));
			}
		}
	}

	size_t Luggage::at_least_one(const string& key) const
	{
		size_t cnt = 0;
		for (const auto& b : _bags)
			if (b.first != key && contains_shiny_gold(b.first, key))
				cnt++;

		return cnt;
	}

	size_t Luggage::count_bags(const string& color) const
	{
		size_t cnt = 0;
		size_t idx = _bags.find(color)->second;
		for (const auto& in : _inside[idx])
			cnt += in.second + in.second * count_bags(in.first);

		return cnt;
	}

	bool Luggage::contains_shiny_gold(const string& color, const string& key) const
	{
		bool result = color == key;
		size_t idx = _bags.find(color)->second;
		for (const auto& in : _inside[idx])
			result |= contains_shiny_gold(in.first, key);

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Luggage(input).at_least_one("shiny gold");
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Luggage(input).count_bags("shiny gold");
	}
}
