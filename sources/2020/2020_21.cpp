#include "2020_21.h"

namespace Day21_2020
{
	Food::Food(const vector<string>& input)
	:	_input(input)
	{
	}

	void Food::solve()
	{
		static const string key = " (contains ";
		for (const auto& s : _input)
		{
			size_t pos = s.find(key);
			auto ing = add_ingredients(s.substr(0, pos));

			string al = s.substr(pos + key.size(), s.size() - key.size() - pos - 1);
			al.erase(std::remove(al.begin(), al.end(), ','), al.end());
			add_allergens(al, ing);
		}

		while (any_of(_allergens.begin(), _allergens.end(), [](const auto& x) { return x.second.size() > 1; }))
		{
			for (const auto& x : _allergens)
				if (x.second.size() == 1)
					for (auto& y : _allergens)
						if (x.first != y.first)
							y.second.erase(*x.second.begin());
		}
	}

	size_t Food::safe_count() const
	{
		vector<bool>safe = vector<bool>(_ingredients.size(), true);
		for (const auto& x : _allergens)
			for (size_t i = 0; i < _ingredients.size(); i++)
				if (_ingredients[i] == *x.second.begin())
					safe[i] = false;

		return count(safe.begin(), safe.end(), true);
	}

	string Food::safe_chain() const
	{
		string s;
		for (const auto& x : _allergens)
			s += *x.second.begin() + ",";

		s.pop_back();
		return s;
	}

	set<string> Food::add_ingredients(const string& input)
	{
		string s;
		stringstream ss(input);
		set<string> ing;
		while (getline(ss, s, ' '))
		{
			_ingredients.push_back(s);
			ing.insert(s);
		}

		return ing;
	}

	void Food::add_allergens(const string& input, const set<string>& ing)
	{
		string s;
		stringstream ss(input);
		while (getline(ss, s, ' '))
		{
			if (_allergens[s].size() == 0)
				_allergens[s].insert(ing.begin(), ing.end());
			else
			{
				auto& allergen_ing = _allergens[s];
				set<string> intersection;
				set_intersection(ing.begin(), ing.end(),
					allergen_ing.begin(), allergen_ing.end(),
					inserter(intersection, intersection.begin()));
				_allergens[s] = move(intersection);
			}
		}
	}

	size_t part_one(const Food& food)
	{
		return food.safe_count();
	}

	string part_two(const Food& food)
	{
		return food.safe_chain();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		Food food(input);
		food.solve();
		auto p1 = part_one(food);
		auto p2 = part_two(food);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(p2);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
