#include "2017_18.h"

namespace Day18_2017
{
	Argument::Argument(const string& s /* = "0" */)
	{
		if (s[0] >= 'a')
		{
			imm = false;
			reg = s[0];
			val = 0;
		}
		else
		{
			imm = true;
			reg = 0;
			val = stoi(s);
		}
	}

	map<string, Operation> Instruction::_map =
	{
		{ "set", Operation::op_set },
		{ "add", Operation::op_add },
		{ "mul", Operation::op_mul },
		{ "mod", Operation::op_mod },
		{ "snd", Operation::op_snd },
		{ "rcv", Operation::op_rcv },
		{ "jgz", Operation::op_jgz }
	};

	Instruction::Instruction(const string& input)
	{
		string s;
		stringstream ss(input);

		getline(ss, s, ' ');
		op = _map.find(s)->second;

		getline(ss, s, ' ');
		dst = Argument(s);

		getline(ss, s, ' ');
		src = Argument(s);
	}

	CPU::CPU()
	:	_other(0), _pc(0), _snd_count(0)
	{
	}

	void CPU::load(CPU* other, const t_program& program, int pvalue)
	{
		_other = other;
		_program = program;
		_regs['p'] = pvalue;
	}

	bool CPU::step()
	{
		if (_pc >= _program.size())
			return false;

		const auto& ins = _program[_pc];
		switch (ins.op)
		{
			case Operation::op_set: { _regs[ins.dst.reg]  = get(ins.src); break; }
			case Operation::op_add: { _regs[ins.dst.reg] += get(ins.src); break; }
			case Operation::op_mul: { _regs[ins.dst.reg] *= get(ins.src); break; }
			case Operation::op_mod: { _regs[ins.dst.reg] %= get(ins.src); break; }

			case Operation::op_snd:
			{
				_snd_count++;
				_other->_queue.push(get(ins.dst));
				break;
			}

			case Operation::op_rcv:
			{
				if (_queue.size() == 0)
					return false;

				_regs[ins.dst.reg] = _queue.front();
				_queue.pop();
				break;
			}

			case Operation::op_jgz:
			{
				if (get(ins.dst) > 0)
					_pc += (get(ins.src) - 1);
			}
		}

		_pc++;
		return true;
	}

	int64_t CPU::get(const Argument& x)
	{
		return x.imm ? x.val : _regs[x.reg];
	}

	t_program Main::load(const vector<string>& input)
	{
		t_program program;
		for (const string& s : input)
			program.push_back(Instruction(s));

		return program;
	}

	// NOTE:
	// Part one seems to be tricky at the first glance, because two cpus are used.
	// If you analyze part two you'll see that part one has to be solved this way
	// to keep the same implementation of CPU::step() for both parts :)

	AoC::Output Main::part_one(const vector<string>& input)
	{
		CPU cpu[2];
		auto program = load(input);
		cpu[0].load(&cpu[1], program, 0);
		cpu[1].load(&cpu[0], program, 1);

		while (cpu[0].step());
		return cpu[1].queue_back();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		CPU cpu[2];
		auto program = load(input);
		cpu[0].load(&cpu[1], program, 0);
		cpu[1].load(&cpu[0], program, 1);

		while (cpu[0].step() || cpu[1].step());
		return cpu[1].snd_count();
	}
}
