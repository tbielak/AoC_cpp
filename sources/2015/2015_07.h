#ifndef __2015_07__
#define __2015_07__

#include "../shared/input_output.h"

namespace Day07_2015
{
	typedef unsigned short int word;
	typedef map<string, word> t_mapIdValues;

	class Argument
	{
	public:
		Argument();
		Argument(const string& s);

		bool immediate;
		string identifier;
		word value;
	};

	typedef vector<Argument> t_vecArgument;

	enum class Operation { op_mov, op_not, op_and, op_or, op_lshift, op_rshift };

	class Instruction
	{
	public:
		Instruction(const string& input);

		bool execute(t_mapIdValues& values) const;
		void replace(const string& id, word value);

	private:
		Operation _op;
		Argument _dst;
		t_vecArgument _src;

		word get(const Argument& arg, const t_mapIdValues& values) const;
	};

	typedef vector<Instruction> t_vecInstruction;

	class CPU
	{
	public:
		static word execute(const t_vecInstruction& instructions);
	};

	t_output main(const t_input& input);
}

#endif
