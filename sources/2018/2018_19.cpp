#include "2018_19.h"

// explained here:
// https://github.com/tbielak/AoC_cpp/blob/master/doc/2018_19.md


namespace Day19_2018
{
	void Main::execute(t_registers& regs, const t_instruction& code)
	{
		switch (code[0])
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

	t_instruction Main::parse(const string& input)
	{
		static map<string, int> opcodes =
		{ {"addr", 0}, {"addi", 1}, {"mulr", 2}, {"muli", 3}, {"banr", 4}, {"bani", 5}, {"borr", 6}, {"bori", 7},
		  {"setr", 8}, {"seti", 9}, {"gtir", 10}, {"gtri", 11}, {"gtrr", 12}, {"eqir", 13}, {"eqri", 14}, {"eqrr", 15} };

		t_instruction code = t_instruction(4);
		code[0] = opcodes[input.substr(0, 4)];
		stringstream ss(input.substr(5));
		for (int i = 1; i < 4; i++)
		{
			ss >> code[i];
			ss.ignore(1);
		}

		return code;
	}

	pair<int, vector<t_instruction>> Main::load(const vector<string>& input)
	{
		int ip = 0;
		vector<t_instruction> program;
		for (const auto& s : input)
		{
			if (s[0] == '#')
				ip = stoi(s.substr(4));
			else
				program.push_back(parse(s));
		}

		return make_pair(ip, program);
	}

	int Main::execute(const vector<string>& input, int R0)
	{
		// run initialization code, using R0, to find R2 value
		auto [ip_reg, program] = load(input);
		t_registers regs = t_registers(6, 0);
		regs[0] = R0;

		while (1)
		{
			int ip = regs[ip_reg];
			if (ip == 1)
				break;

			execute(regs, program[ip]);
			regs[ip_reg]++;
		}

		// find factors of R2 (excluding 1 and R2)
		int n = regs[2];
		vector<int> factors;
		for (int k = 2; n > 1 && k * k <= n; k++)
			while (n % k == 0)
			{
				factors.push_back(k);
				n /= k;
			}

		if (n > 1)
			factors.push_back(n);

		// find set of R1 values
		set<int> R1;

		int all = 1 << (int)factors.size();
		for (int mask = 0; mask < all; mask++)
		{
			int number = 1;
			for (int i = 0; i < (int)factors.size(); i++)
				if (mask & (1 << i))
					number *= factors[i];

			R1.insert(number);
		}

		// sum R1
		return accumulate(R1.begin(), R1.end(), 0, [](int sum, const auto& v) { return sum + v; });
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return execute(input, 0);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return execute(input, 1);
	}
}
