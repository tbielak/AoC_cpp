#include "2022_05.h"

namespace Day05_2022
{
	tuple<t_stacks, t_moves> Main::load(const vector<string>& input)
	{
		t_stacks stacks;
		t_moves moves;

		// find stack ids
		int idx = 0;
		while (!input[idx].empty()) idx++;

		vector<int> ids;
		for (size_t i = 1; i < input[idx - 1].size(); i += 4)
		{
			int id = input[idx - 1][i] - '0';
			ids.push_back(id);
			stacks[id] = "";
		}

		// read stacks contents
		for (int i = idx - 2; i >= 0; i--)
			for (size_t j = 0; j < ids.size(); j++)
				if (input[i][j * 4 + 1] != ' ')
					stacks[ids[j]] += input[i][j * 4 + 1];

		// read moves
		smatch matches;
		regex regex("move ([0-9]*) from ([0-9]*) to ([0-9]*)");
		for (size_t i = idx + 1; i < input.size(); i++)
		{
			regex_search(input[i], matches, regex);
			moves.push_back(make_tuple(stoi(matches[1].str()), stoi(matches[2].str()), stoi(matches[3].str())));
		}

		return make_tuple(stacks, moves);
	}

	string Main::print(const t_stacks& stacks)
	{
		string s;
		for (const auto& it : stacks)
			s += it.second.back();

		return s;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [stacks, moves] = load(input);
		for (auto [count, from, to] : moves)
			for (int i = 0; i < count; i++)
			{
				stacks[to] += stacks[from].back();
				stacks[from].pop_back();
			}

		return print(stacks);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [stacks, moves] = load(input);
		for (auto [count, from, to] : moves)
		{
			string tmp;
			for (int i = 0; i < count; i++)
			{
				tmp = stacks[from].back() + tmp;
				stacks[from].pop_back();
			}

			stacks[to] += tmp;
		}

		return print(stacks);
	}
}
