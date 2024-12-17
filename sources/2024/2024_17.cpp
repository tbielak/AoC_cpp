#include "2024_17.h"

namespace Day17_2024
{
	pair<vector<int64_t>, string> Main::load(const vector<string>& input)
	{
		vector<int64_t> regs = vector<int64_t>(3);
		for (int i = 0; i < 3; i++)
			regs[i] = stoll(input[i].substr(input[i].find_first_of(':') + 2));

		return make_pair(regs, input[4].substr(input[4].find_first_of(':') + 2));
	}

	int64_t Main::combo(const vector<int64_t>& regs, int op)
	{
		return op < 4 ? op : regs[op - 4];
	}

	string Main::execute(vector<int64_t>& regs, string program)
	{
		string output;
		size_t pc = 0;
		while (pc < program.size())
		{
			int mn = program[pc] - '0';
			int op = program[pc + 2] - '0';
			pc += 4;

			switch (mn)
			{
			case 0: regs[0] = regs[0] / (1LL << combo(regs, op)); break;
			case 1: regs[1] ^= op; break;
			case 2: regs[1] = combo(regs, op) & 7; break;
			case 3: if (regs[0] != 0) pc = op; break;
			case 4: regs[1] ^= regs[2]; break;
			case 5: {
				if (!output.empty())
					output += ",";

				output += char((combo(regs, op) & 7) + '0');
				break;
			}
			case 6: regs[1] = regs[0] / (1LL << combo(regs, op)); break;
			case 7: regs[2] = regs[0] / (1LL << combo(regs, op)); break;
			}
		}
		return output;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [regs, program] = load(input);
		return execute(regs, program);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [regs, program] = load(input);
		size_t idx = program.size() - 1;
		
		int64_t A = 0;
		for (; ; A++)
		{
			regs[0] = A;
			if (execute(regs, program) == program.substr(idx))
			{
				if (idx == 0)
					break;

				idx -= 2;
				A = A * 8 - 8;
			}
		}

		return A;
	}
}
