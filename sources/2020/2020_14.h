#ifndef __2020_14__
#define __2020_14__

#include "../shared/Solution.h"

namespace Day14_2020
{
	class Instruction
	{
	public:
		Instruction(uint64_t address, uint64_t value);
		Instruction(uint64_t p1or, uint64_t p1and, uint64_t p2or, uint64_t p2and);

		bool store;
		uint64_t address, value;

		// two masks (or, and) for part one and part two
		uint64_t or_mask[2];
		uint64_t and_mask[2];
	};

	typedef map<uint64_t, uint64_t> t_memory;		// address to value

	class InitializationProgram
	{
	public:
		InitializationProgram(const vector<string>& input);

		uint64_t execute(size_t mask_index, void(*store_function)(t_memory&, uint64_t, uint64_t, uint64_t, uint64_t)) const;

	private:
		vector<Instruction> _code;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
