#include "2022_11.h"

namespace Day11_2022
{
	Monkey::Monkey(const string& items, const string& operation,
		const string& divisible, const string& true_target, const string& false_target)
	{
		load_items(items.substr(items.find_first_of(":") + 2));
		load_operation(operation.substr(operation.find_first_of("=") + 2));
		_divisible = stoi(divisible.substr(divisible.find("by ") + 3));
		_target.push_back(stoi(false_target.substr(false_target.find("false: throw to monkey ") + 23)));
		_target.push_back(stoi(true_target.substr(true_target.find("true: throw to monkey ") + 22)));
	}

	pair<size_t, int64_t> Monkey::turn(size_t idx, int decrease_worry_level)
	{
		int64_t w = _operation_fn(_items[idx], _value) / decrease_worry_level;
		return make_pair(_target[(w % _divisible) == 0], w);
	}

	void Monkey::add_item(int64_t value)
	{
		_items.push_back(value);
	}

	void Monkey::clear_items()
	{
		_items.clear();
	}

	int Monkey::divisible() const
	{
		return _divisible;
	}

	size_t Monkey::items_count() const
	{
		return _items.size();
	}

	void Monkey::load_items(const string& items)
	{
		string s;
		stringstream ss(items);
		while (getline(ss, s, ','))
			_items.push_back(stoi(s));
	}

	void Monkey::load_operation(const string& operation)
	{
		if (operation == "old * old")
		{
			_value = 0;
			_operation_fn = [](int64_t a, int64_t b) { (void)(b); return a * a; };
			return;
		}

		_value = stoi(operation.substr(6));
		if (operation[4] == '*')
			_operation_fn = [](int64_t a, int64_t b) { return a * b; };
		else
			_operation_fn = [](int64_t a, int64_t b) { return a + b; };
	}

	vector<Monkey> Main::load(const vector<string>& input)
	{
		vector<Monkey> monkeys;
		for (size_t idx = 0; idx < input.size(); idx += 7)
			monkeys.push_back(Monkey(input[idx+1], input[idx+2], input[idx+3], input[idx+4], input[idx+5]));

		return monkeys;
	}

	int64_t Main::keep_away(vector<Monkey> monkeys, int rounds, int decrease_worry_level)
	{
		int product = 1;
		for (const auto& m : monkeys)
			product *= m.divisible();

		vector<int64_t> inspection_count = vector<int64_t>(monkeys.size(), 0);
		for (int r = 0; r < rounds; r++)
			for (size_t m = 0; m < monkeys.size(); m++)
			{
				for (size_t i = 0; i < monkeys[m].items_count(); i++)
				{
					inspection_count[m]++;
					auto [target, value] = monkeys[m].turn(i, decrease_worry_level);
					monkeys[target].add_item(value % product);
				}

				monkeys[m].clear_items();
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
