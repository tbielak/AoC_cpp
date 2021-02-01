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

	size_t part_one(const Luggage& luggage)
	{
		return luggage.at_least_one("shiny gold");
	}

	size_t part_two(const Luggage& luggage)
	{
		return luggage.count_bags("shiny gold");
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		Luggage luggage(input);
		auto p1 = part_one(luggage);
		auto p2 = part_two(luggage);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
