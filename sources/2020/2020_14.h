#ifndef __2020_14__
#define __2020_14__

#include "../shared/input_output.h"

namespace Day14_2020
{
	class Instruction
	{
	public:
		Instruction(uintmax_t address, uintmax_t value);
		Instruction(uintmax_t p1or, uintmax_t p1and, uintmax_t p2or, uintmax_t p2and);

		bool store;
		uintmax_t address, value;

		// two masks (or, and) for part one and part two
		uintmax_t or_mask[2];
		uintmax_t and_mask[2];
	};

	typedef map<uintmax_t, uintmax_t> t_memory;		// address to value

	class InitializationProgram
	{
	public:
		InitializationProgram(const vector<string>& input);

		uintmax_t execute(size_t mask_index, void(*store_function)(t_memory&, uintmax_t, uintmax_t, uintmax_t, uintmax_t)) const;

	private:
		vector<Instruction> _code;
	};

	t_output main(const t_input& input);
}

#endif
