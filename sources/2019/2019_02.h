#ifndef __2019_02__
#define __2019_02__

#include "../shared/input_output.h"

namespace Day02_2019
{
	// Intcode Virtual Machine version 1 (2019/02)
	//
	// features:
	// - loading code into the memory
	// - patching the memory
	// - instructions: addition, multiplication and halt
	// - peeking the memory

	typedef map<int, int> t_Memory;  // address to value

	class IntcodeVM
	{
	public:
		static t_Memory parse(const string& input);

		IntcodeVM(const t_Memory& program);
		void patch(int address, int value);
		void run();
		int mem(int address);

	private:
		int _ip;
		t_Memory _memory;
		enum class Operation { addition = 1, multiplication = 2, halt = 99 };

		int fetch();
		void store(int v);
	};

	t_output main(const t_input& input);
}

#endif
