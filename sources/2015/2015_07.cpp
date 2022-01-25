#include "2015_07.h"

namespace Day07_2015
{
	Argument::Argument()
	:	immediate(true), value(0)
	{
	}

	Argument::Argument(const string& s)
	{
		if (s[0] >= '0' && s[0] <= '9')
		{
			immediate = true;
			value = (word)stoi(s);
		}
		else
		{
			immediate = false;
			identifier = s;
			value = 0;
		}
	}

	Instruction::Instruction(const string& input)
	:	_op(Operation::op_mov)
	{
		bool target = false;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ' '))
		{
			if ("NOT" == s) { _op = Operation::op_not; continue; }
			if ("AND" == s) { _op = Operation::op_and; continue; }
			if ("OR" == s) { _op = Operation::op_or; continue; }
			if ("LSHIFT" == s) { _op = Operation::op_lshift; continue; }
			if ("RSHIFT" == s) { _op = Operation::op_rshift; continue; }
			if ("->" == s) { target = true; continue; }
			if (target)
				_dst = Argument(s);
			else
				_src.push_back(Argument(s));
		}
	}

	bool Instruction::execute(t_mapIdValues& values) const
	{
		bool available = true;
		for (const auto& s : _src)
			if (!s.immediate && values.find(s.identifier) == values.end())
				available = false;

		if (!available)
			return false;

		switch (_op)
		{
			case Operation::op_not: { values[_dst.identifier] = get(_src[0], values) ^ 0xFFFF; break; }
			case Operation::op_and: { values[_dst.identifier] = get(_src[0], values) & get(_src[1], values); break; }
			case Operation::op_or: { values[_dst.identifier] = get(_src[0], values) | get(_src[1], values); break; }
			case Operation::op_lshift: { values[_dst.identifier] = (word)(get(_src[0], values) << get(_src[1], values)); break; }
			case Operation::op_rshift: { values[_dst.identifier] = (word)(get(_src[0], values) >> get(_src[1], values)); break; }
			default: /* op_mov */ { values[_dst.identifier] = get(_src[0], values); break; }
		}

		return true;
	}

	void Instruction::replace(const string& id, word value)
	{
		if (_dst.identifier == id && _op == Operation::op_mov && _src[0].immediate)
			_src[0].value = value;
	}

	word Instruction::get(const Argument& arg, const t_mapIdValues& values) const
	{
		return (arg.immediate) ? arg.value : values.find(arg.identifier)->second;
	}

	word CPU::execute(const t_vecInstruction& instructions)
	{
		t_mapIdValues values;
		vector<bool> instructionsProcessed(instructions.size());
		while (1)
		{
			bool allProcessed = true;
			int current = 0;
			for (const auto& i : instructions)
			{
				if (!instructionsProcessed[current])
				{
					if (i.execute(values))
						instructionsProcessed[current] = true;
					else
						allProcessed = false;
				}

				current++;
			}

			if (allProcessed)
				break;
		}

		return values.find("a")->second;
	}

	Main::Main()
	:	_wire_a(0)
	{
	}

	t_vecInstruction Main::load(const vector<string>& input)
	{
		t_vecInstruction instructions;
		for (const auto& line : input)
			instructions.push_back(Instruction(line));

		return instructions;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_vecInstruction instructions = load(input);
		_wire_a = CPU::execute(instructions);
		return _wire_a;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_vecInstruction instructions = load(input);
		for (auto& i : instructions)
			i.replace("b", _wire_a);

		return CPU::execute(instructions);
	}
}
