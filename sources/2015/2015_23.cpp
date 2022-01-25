#include "2015_23.h"

namespace Day23_2015
{
	Instruction::Instruction(const string& input)
	{
		reg = -1;
		offs = 0;
		int position = 0;
		mnemonic = mnemonic_map.find(input.substr(0, 3))->second;

		if (input[4] == 'a' || input[4] == 'b')
		{
			reg = input[4] - 'a';
			if (input.size() > 5)
				position = 7;
		}
		else
			if (input[4] == '+' || input[4] == '-')
				position = 4;

		if (position > 0)
			offs = stoi(input.substr(position));
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		t_vecInstruction code;
		for (const auto& line : input)
			code.push_back(Instruction(line));

		vector<int> result;
		for (int part = 1; part <= 2; part++)
		{
			vector<int> regs = { part - 1, 0 };
			int pc = 0;
			while (pc >= 0 && pc < (int)code.size())
			{
				const auto& ins = code[pc];
				switch (ins.mnemonic)
				{
					case M::hlf: { regs[ins.reg] /= 2; pc++;  break; }
					case M::tpl: { regs[ins.reg] *= 3; pc++; break; }
					case M::inc: { regs[ins.reg]++; pc++; break; }
					case M::jmp: { pc += ins.offs; break; }
					case M::jie: { if ((regs[ins.reg] & 1) == 0) pc += ins.offs; else pc++; break; }
					case M::jio: { if (regs[ins.reg] == 1) pc += ins.offs; else pc++; break; }
					default: throw;
				}
			}

			result.push_back(regs[1]);
		}

		return result;
	}
}
