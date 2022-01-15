#include "2016_12.h"

namespace Day12_2016
{
	Argument::Argument(int value /* = 0 */)
	:	imm(true), value(value)
	{
	}
		
	Argument::Argument(char reg)
	:	imm(false), value(reg - 'a')
	{
	}

	Instruction::Instruction(char op, const Argument& x, const Argument& y)
	:	op(op), x(x), y(y)
	{
	}

	VM::VM(const t_input& program)
	{
		_regs = vector<int>(4, 0);
		for (const auto& s : program)
		{
			char op = s[0];

			Argument src = (s[4] >= 'a' && s[4] <= 'd')
				? Argument(s[4]) : Argument(stoi(s.substr(4)));

			Argument dst;
			if (op == 'c' || op == 'j')
				dst = (s.back() >= 'a' && s.back() <= 'd')
				? Argument(s.back()) : Argument(stoi(s.substr(s.find_last_of(' ') + 1)));

			_code.push_back(Instruction(op, src, dst));
		}
	}

	VM& VM::init(char r, int value)
	{
		_regs[r - 'a'] = value;
		return* this;
	}

	VM& VM::run()
	{
		int pc = 0;
		while (pc < (int)_code.size())
		{
			const auto& ins = _code[pc];
			switch (ins.op)
			{
				case 'c': _regs[ins.y.value] = value(ins.x); break;
				case 'i': _regs[ins.x.value]++; break;
				case 'd': _regs[ins.x.value]--; break;
				default:
					if (value(ins.x) != 0)
						pc += (value(ins.y) - 1);

					break;
			}

			pc++;
		}

		return *this;
	}

	int VM::reg(char r) const
	{
		return _regs[r - 'a'];
	}

	int VM::value(const Argument& a) const
	{
		return a.imm ? a.value : _regs[a.value];
	}

	int part_one(const t_input& input)
	{
		return VM(input).run().reg('a');
	}

	int part_two(const t_input& input)
	{
		return VM(input).init('c', 1).run().reg('a');
	}

	t_output main(const t_input& input)
	{
		VM vm(input);
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
