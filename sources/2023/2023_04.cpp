#include "2023_04.h"

namespace Day04_2023
{
	Numbers Main::load(const string& s)
	{
		Numbers numbers;
		for (int i = 0; i < (int)s.size(); i += 3)
			numbers.insert(stoi(s.substr(i)));

		return numbers;
	}

	Cards Main::load(const vector<string>& input)
	{
		Cards cards;
		for (const string& s : input)
		{
			int id = stoi(s.substr(4));
			string c = s.substr(s.find(":") + 2);
			size_t pos = c.find("|");
			auto winning = load(c.substr(0, pos - 1));
			auto yours = load(c.substr(pos + 2));

			int count = 0;
			for (auto v : yours)
				if (winning.find(v) != winning.end())
					count++;

			cards[id] = count;
		}

		return cards;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int sum = 0;
		for (const auto& [id, count] : load(input))
			if (count > 0)
				sum += (1 << (count - 1));

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		map<int, int> instances;
		for (const auto& [id, count] : load(input))
		{
			instances[id]++;
			int current_instances = instances[id];
			for (int i = 1; i <= count; i++)
				instances[id + i] += current_instances;
		}

		int sum = 0;
		for (const auto& x : instances)
			sum += x.second;

		return sum;
	}
}
