#include "2020_08.h"

namespace Day08_2020
{
	t_code Main::load(const vector<string>& input)
	{
		t_code code;
		for (const auto& line : input)
			code.push_back(make_pair(line[0], stoi(line.substr(4))));

		return code;
	}

	bool Main::run(const t_code& code, int& acc)
	{
		size_t pc = 0;
		vector<bool> visited(code.size());
		while (1)
		{
			if (pc >= code.size())
				break;			  // ended

			if (visited[pc])
				return false;	   // infinite loop

			visited[pc] = true;
			if (code[pc].first == 'a') acc += code[pc].second;
			if (code[pc].first == 'j') pc += (code[pc].second - 1);
			pc++;
		}

		return true;
	}

	pair<bool, int> Main::fix_and_run(t_code& code, char from, char to)
	{
		for (size_t i = 0; i < code.size(); i++)
			if (code[i].first == from)
			{
				code[i].first = to;
				int acc = 0;
				bool ended = run(code, acc);
				code[i].first = from;
				if (ended)
					return make_pair(true, acc);
			}

		return make_pair(false, -1);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int acc = 0;
		run(load(input), acc);
		return acc;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto code = load(input);

		auto x = fix_and_run(code, 'j', 'n');
		if (x.first)
			return x.second;

		x = fix_and_run(code, 'n', 'j');
		if (x.first)
			return x.second;

		return -1;
	}
}
