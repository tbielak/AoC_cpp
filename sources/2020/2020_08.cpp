#include "2020_08.h"

namespace Day08_2020
{
	bool run(const t_code& code, int& acc)
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

	pair<bool, int> fix_and_run(t_code& code, char from, char to)
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

	int part_one(const t_code& code)
	{
		int acc = 0;
		run(code, acc);
		return acc;
	}

	int part_two(t_code& code)
	{
		auto x = fix_and_run(code, 'j', 'n');
		if (x.first)
			return x.second;

		x = fix_and_run(code, 'n', 'j');
		if (x.first)
			return x.second;

		return -1;
	}

	t_output main(const t_input& input)
	{
		t_code code;
		for (const auto& line : input)
			code.push_back(make_pair(line[0], stoi(line.substr(4))));

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(code);
		auto p2 = part_two(code);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
