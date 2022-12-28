#include "2018_16.h"

namespace Day16_2018
{
	Sample::Sample(const string& before_str, const string& code_str, const string& after_str)
	{
		before = parse(clean(before_str));
		code = parse(clean(code_str));
		after = parse(clean(after_str));
	}

	vector<int> Sample::parse(const string& input)
	{
		vector<int> result = vector<int>(4);
		stringstream ss(input);
		for (int i = 0; i < 4; i++)
		{
			ss >> result[i];
			ss.ignore(1);
		}

		return result;
	}

	string Sample::clean(const string& input) const
	{
		string s;
		for (char c : input)
			if ((c >= '0' && c <= '9') || (s.size() > 0 && c == ' '))
				s += c;

		return s;
	}

	pair<vector<Sample>, vector<vector<int>>> Main::load(const vector<string>& input)
	{
		vector<Sample> samples;
		int i = 0;
		for (; input[i].size() > 0; i += 4)
			samples.push_back(Sample(input[i], input[i + 1], input[i + 2]));

		while (input[i].size() == 0)
			i++;

		vector<vector<int>> program;
		for (; i < (int)input.size(); i++)
			program.push_back(Sample::parse(input[i]));

		return make_pair(samples, program);
	}

	void Main::execute(int op, vector<int>& regs, const vector<int>& code)
	{
		switch (op)
		{
			case 0: regs[code[3]] = regs[code[1]] + regs[code[2]]; break; // addr
			case 1: regs[code[3]] = regs[code[1]] + code[2]; break; // addi
			case 2: regs[code[3]] = regs[code[1]] * regs[code[2]]; break; // mulr
			case 3: regs[code[3]] = regs[code[1]] * code[2]; break; // muli
			case 4: regs[code[3]] = regs[code[1]] & regs[code[2]]; break; // banr
			case 5: regs[code[3]] = regs[code[1]] & code[2]; break; // bani
			case 6: regs[code[3]] = regs[code[1]] | regs[code[2]]; break; // borr
			case 7: regs[code[3]] = regs[code[1]] | code[2]; break; // bori
			case 8: regs[code[3]] = regs[code[1]]; break; // setr
			case 9: regs[code[3]] = code[1]; break; // seti
			case 10: regs[code[3]] = code[1] > regs[code[2]] ? 1 : 0; break; // gtir
			case 11: regs[code[3]] = regs[code[1]] > code[2] ? 1 : 0; break; // gtri
			case 12: regs[code[3]] = regs[code[1]] > regs[code[2]] ? 1 : 0; break; // gtrr
			case 13: regs[code[3]] = code[1] == regs[code[2]] ? 1 : 0; break; // eqir
			case 14: regs[code[3]] = regs[code[1]] == code[2] ? 1 : 0; break; // eqri
			default: regs[code[3]] = regs[code[1]] == regs[code[2]] ? 1 : 0; break; // eqrr
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [samples, program] = load(input);
		
		int count = 0;
		for (const auto& [before, code, after] : samples)
		{
			int c = 0;
			for (int op = 0; op < 16; op++)
			{
				vector<int> regs = before;
				execute(op, regs, code);
				if (regs == after)
					c++;
			}

			if (c >= 3)
				count++;
		}

		return count;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [samples, program] = load(input);

		map<int, int> op_map;
		while (op_map.size() < 16)
		{
			for (const auto& [before, code, after] : samples)
			{
				int c = 0;
				int found = -1;
				for (int op = 0; op < 16; op++)
				{
					if (op_map.find(op) != op_map.end())
						continue;

					vector<int> regs = before;
					execute(op, regs, code);
					if (regs == after)
					{
						found = op;
						c++;
					}
				}

				if (c == 1)
				{
					op_map[found] = code[0];
					break;
				}
			}
		}
		
		map<int, int> rev_op_map;
		for (const auto& it : op_map)
			rev_op_map[it.second] = it.first;

		vector<int> regs = vector<int>(4, 0);
		for (const auto& code : program)
			execute(rev_op_map[code[0]], regs, code);
		
		return regs[0];
	}
}
