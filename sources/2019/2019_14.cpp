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

	intmax_t Reactions::produce_fuel(intmax_t amount) const
	{
		vector<intmax_t> taken = vector<intmax_t>(_chemicals.size(), 0);
		taken[0] = amount;

		for (size_t i = 0; i < _chemicals.size(); i++)
		{
			if (taken[i] == 0)
				continue;

			intmax_t x = (taken[i] + _chemicals[i].target.count - 1) / _chemicals[i].target.count;

			for (auto const& ing : _chemicals[i].ingredients)
				taken[_names.find(ing.name)->second] += x * ing.count;
		}

		return taken.back();
	}

	intmax_t Reactions::target_ore(intmax_t ore) const
	{
		intmax_t left = ore / produce_fuel(1);
		intmax_t right = left * 2;
		intmax_t x = -1;
		intmax_t prod = -1;

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

	intmax_t part_one(const Reactions& reactions)
	{
		return reactions.produce_fuel(1);
	}

	intmax_t part_two(const Reactions& reactions)
	{
		return reactions.target_ore(1000000000000);
	}

	t_output main(const t_input& input)
	{
		Reactions reactions;
		for (auto line : input)
		{
			if (line == "")
				break;

			reactions.add(line);
		}

		reactions.prepare();

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(reactions);
		auto p2 = part_two(reactions);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
