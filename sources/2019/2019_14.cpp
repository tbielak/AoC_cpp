#include "2019_14.h"

namespace Day14_2019
{
	Ingredient::Ingredient()
	:	count(0)
	{
	}

	Ingredient::Ingredient(const string& input)
	{
		size_t separator = input.find_first_of(' ');
		count = stoi(input.substr(0, separator));
		name = input.substr(separator + 1);
	}

	Chemical::Chemical(const string& ingredients_string, const string& target, int order /* = -1 */)
	:	order(order), target(target)
	{
		string s;
		stringstream ss(ingredients_string);
		while (getline(ss, s, ','))
			ingredients.push_back(Ingredient(ltrim(s)));
	}

	string Chemical::ltrim(const string& s)
	{
		size_t pos = s.find_first_not_of(" ");
		return (pos == string::npos) ? "" : s.substr(pos);
	}

	Reactions::Reactions(const vector<string>& input)
	{
		for (auto line : input)
		{
			if (line == "")
				break;

			add(line);
		}

		prepare();
	}

	void Reactions::add(const string& line)
	{
		size_t pos = line.find(" => ");
		_chemicals.push_back(Chemical(line.substr(0, pos), line.substr(pos + 4)));
	}

	void Reactions::prepare()
	{
		_chemicals.push_back(Chemical("", "1 ORE", INT_MAX));
		update_names_mapping();
			
		order_recursive("FUEL", 0);
		stable_sort(_chemicals.begin(), _chemicals.end(), sort_proc);
		update_names_mapping();
	}

	int64_t Reactions::produce_fuel(int64_t amount) const
	{
		vector<int64_t> taken = vector<int64_t>(_chemicals.size(), 0);
		taken[0] = amount;

		for (size_t i = 0; i < _chemicals.size(); i++)
		{
			if (taken[i] == 0)
				continue;

			int64_t x = (taken[i] + _chemicals[i].target.count - 1) / _chemicals[i].target.count;

			for (auto const& ing : _chemicals[i].ingredients)
				taken[_names.find(ing.name)->second] += x * ing.count;
		}

		return taken.back();
	}

	int64_t Reactions::target_ore(int64_t ore) const
	{
		int64_t left = ore / produce_fuel(1);
		int64_t right = left * 2;
		int64_t x = -1;
		int64_t prod = -1;

		while (left < right)
		{
			x = (left + right) / 2;
			prod = produce_fuel(x);

			if (prod == ore)
				break;

			if (prod > ore)
			{
				if (right == x)
					break;

				right = x;
			}

			if (prod < ore)
			{
				if (left == x)
					break;

				left = x;
			}
		}

		return x;
	}

	bool Reactions::sort_proc(const Chemical& x1, const Chemical& x2)
	{
		return x1.order < x2.order;
	}
	
	void Reactions::order_recursive(const string& name, int order)
	{
		Chemical& ch = _chemicals[_names.find(name)->second];
		if (ch.order < order)
			ch.order = order;

		order++;

		for (auto ing : ch.ingredients)
		{
			if (ing.name != "ORE")
				order_recursive(ing.name, order);
		}
	}

	void Reactions::update_names_mapping()
	{
		for (size_t idx = 0; idx < _chemicals.size(); idx++)
			_names[_chemicals[idx].target.name] = idx;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Reactions(input).produce_fuel(1);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Reactions(input).target_ore(1000000000000);
	}
}
