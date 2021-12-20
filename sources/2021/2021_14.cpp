#include "2021_14.h"

namespace Day14_2021
{
	intmax_t solve(const t_input& input, int steps)
	{
		// count pair of chars in input
		t_polymer polymer;
		const string& input_polymer = input[0];
		for (size_t i = 0; i < input_polymer.size() - 1; i++)
			polymer[input_polymer.substr(i, 2)]++;

		// load rules
		t_rules rules;
		for (size_t i = 2; i < input.size(); i++)
			rules[input[i].substr(0, 2)] = input[i][6];

		// new pairs on insertion
		string a = "??";
		string b = "??";

		// go requested number of steps
		for (int s = 0; s < steps; s++)
		{
			// create new polymer
			t_polymer new_polymer = polymer;

			// check each pair of chars...
			for (const auto& p : polymer)
			{
				// and find a rule to apply
				const auto& it = rules.find(p.first);
				if (it == rules.end())
					continue;

				// pair p.first is split into two pairs: a and b
				a[0] = p.first[0];
				a[1] = it->second;
				b[0] = it->second;
				b[1] = p.first[1];

				// decrease number of p.first pairs
				new_polymer.find(p.first)->second -= p.second;

				// increase number of a and b pairs
				new_polymer[a] += p.second;
				new_polymer[b] += p.second;
			}

			// assign new polymer to the old one, and proceed to the next step
			polymer = new_polymer;
		}

		// elements quantity
		t_elements quantity;
		quantity[input_polymer[0]]++;
		for (const auto& p : polymer)
			quantity[p.first[1]] += p.second;

		// create reverse map (quantity to elements)
		t_elements_rev rev;
		for (const auto& it : quantity)
			rev[it.second] = it.first;

		// most common element - least common element
		return rev.rbegin()->first - rev.begin()->first;
	}

	intmax_t part_one(const t_input& input)
	{
		return solve(input, 10);
	}

	intmax_t part_two(const t_input& input)
	{
		return solve(input, 40);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
