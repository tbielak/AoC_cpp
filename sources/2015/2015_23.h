#ifndef __2015_23__
#define __2015_23__

#include "../shared/input_output.h"

namespace Day23_2015
{
	enum class M { hlf, tpl, inc, jmp, jie, jio };

	const map<string, M> mnemonic_map = {
		{ "hlf", M::hlf }, { "tpl", M::tpl }, { "inc", M::inc },
		{ "jmp", M::jmp }, { "jie", M::jie }, { "jio", M::jio } };

	class Instruction
	{
	public:
		Instruction(const string& input);

		M mnemonic;
		int reg;
		int offs;
	};

	typedef vector<Instruction> t_vecInstruction;

	t_output main(const t_input& input);
}

#endif
