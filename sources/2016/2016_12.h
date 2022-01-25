#ifndef __2016_12__
#define __2016_12_

#include "../shared/Solution.h"

namespace Day12_2016
{
	class Argument
	{
	public:
		Argument(int value = 0);
		Argument(char reg);

		bool imm;
		int value;
	};

	class Instruction
	{
	public:
		Instruction(char op, const Argument& x, const Argument& y);

		char op;
		Argument x, y;
	};

	typedef vector<Instruction> t_code;
	typedef vector<int> t_regs;

	class VM
	{
	public:
		VM(const vector<string>& program);

		VM& init(char r, int value);
		VM& run();

		int reg(char r) const;

	private:
		t_code _code;
		t_regs _regs;

		int value(const Argument& a) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
