#include "2024_05.h"

namespace Day05_2024
{
	pair<t_updates, t_predecessors> Main::load(const vector<string>& input)
	{
		size_t i = 0;
		t_predecessors predecessors;
		for (; !input[i].empty(); i++)
		{
			size_t pos = input[i].find("|");
			int prev = stoi(input[i].substr(0, pos));
			int next = stoi(input[i].substr(pos + 1));
			auto it = predecessors.find(prev);
			if (it == predecessors.end())
				predecessors[prev] = set<int>();

			predecessors[next].insert(prev);
		}

		t_updates updates;
		for (++i; i < input.size(); i++)
		{
			updates.push_back(vector<int>());
			string v;
			stringstream ss(input[i]);
			while (getline(ss, v, ','))
				updates.back().push_back(stoi(v));
		}

		return make_pair(updates, predecessors);
	}

	bool Main::ordered(const vector<int>& pages, const t_predecessors& predecessors)
	{
		for (size_t i = 1; i < pages.size(); i++)
		{
			const auto& preds = predecessors.find(pages[i])->second;
			for (size_t j = 0; j < i; j++)
				if (preds.find(pages[j]) == preds.end())
					return false;
		}

		return true;
	}

	vector<int> Main::fixed_order(const vector<int>& pages, const t_predecessors& predecessors)
	{
		map<int, set<int>> predecessors_subset;
		for (auto p : pages)
			predecessors_subset[p] = set<int>();

		for (auto& [page_subset, required_subset] : predecessors_subset)
		{
			const auto& required = predecessors.find(page_subset)->second;
			for (const auto& [page, _] : predecessors_subset)
				if (required.find(page) != required.end())
					required_subset.insert(page);
		}

		map<size_t, int> ordered;
		for (const auto& [page, requires] : predecessors_subset)
			ordered[requires.size()] = page;

		vector<int> output;
		for (const auto [_, page] : ordered)
			output.push_back(page);

		return output;
	}
	
	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [updates, predecessors] = load(input);

		int sum = 0;
		for (const auto& pages : updates)
			if (ordered(pages, predecessors))
				sum += pages[pages.size() / 2];
		
		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [updates, predecessors] = load(input);

		int sum = 0;
		for (const auto& pages : updates)
			if (!ordered(pages, predecessors))
			{
				auto fixed = fixed_order(pages, predecessors);
				sum += fixed[fixed.size() / 2];
			}

		return sum;
	}
}
