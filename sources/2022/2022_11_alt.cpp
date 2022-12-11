#include "2022_11_alt.h"

namespace Day11_2022_Alt
{
	Monkey::Monkey(const string& items_str, const string& operation_str,
		const string& divisible_str, const string& true_target_str, const string& false_target_str)
	{
		load_items(items_str.substr(items_str.find_first_of(":") + 2));
		load_operation(operation_str.substr(operation_str.find_first_of("=") + 2));
		divisible = stoi(divisible_str.substr(divisible_str.find("by ") + 3));
		target.push_back(stoi(false_target_str.substr(false_target_str.find("false: throw to monkey ") + 23)));
		target.push_back(stoi(true_target_str.substr(true_target_str.find("true: throw to monkey ") + 22)));
	}

	void Monkey::load_items(const string& items_str)
	{
		string s;
		stringstream ss(items_str);
		while (getline(ss, s, ','))
			items.push_back(stoi(s));
	}

	void Monkey::load_operation(const string& operation_str)
	{
		if (operation_str == "old * old")
		{
			value = 0;
			compute = &compute_power;
			return;
		}

		value = stoi(operation_str.substr(6));
		compute = (operation_str[4] == '*') ? &compute_mult : &compute_add;
	}

	vector<Monkey> Main::load(const vector<string>& input)
	{
		vector<Monkey> monkeys;
		for (size_t idx = 0; idx < input.size(); idx += 7)
			monkeys.push_back(Monkey(input[idx + 1], input[idx + 2], input[idx + 3], input[idx + 4], input[idx + 5]));

		return monkeys;
	}

	int64_t Main::keep_away(vector<Monkey> monkeys, int rounds, int decrease_worry_level)
	{
		int product = 1;
		for (const auto& m : monkeys)
			product *= m.divisible;

		vector<int64_t> inspection_count = vector<int64_t>(monkeys.size(), 0);
		for (int r = 0; r < rounds; r++)
			for (size_t m = 0; m < monkeys.size(); m++)
			{
				for (size_t i = 0; i < monkeys[m].items.size(); i++)
				{
					inspection_count[m]++;
					int64_t value = monkeys[m].compute(monkeys[m].items[i], monkeys[m].value) / decrease_worry_level;
					monkeys[monkeys[m].target[(value % monkeys[m].divisible) == 0]].items.push_back(value % product);
				}

				monkeys[m].items.clear();
			}

		sort(inspection_count.begin(), inspection_count.end(), greater<int64_t>());
		return inspection_count[0] * inspection_count[1];
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return keep_away(load(input), 20, 3);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return keep_away(load(input), 10000, 1);
	}
}
