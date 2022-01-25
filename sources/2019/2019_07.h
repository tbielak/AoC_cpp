#ifndef __2019_07__
#define __2019_07__

#include "../shared/Solution.h"

namespace Day07_2019
{
	// Intcode Virtual Machine version 3
	//
	// added in version 3 (2019/07):
	// - introducing machine state
	// - signaling wait_for_input, output_ready or halted on run() method executed
	// - ability to restart existing program
	//
	// added in version 2 (2019/05):
	// - inputs and outputs
	// - position and immediate modes
	// - new instructions: get_input, put_output, jump_if_true, jump_if_false, less_than, equals
	//
	// features of version 1 (2019/02):
	// - loading code into the memory
	// - patching the memory
	// - instructions: addition, multiplication and halt
	// - peeking the memory

	typedef map<int, int> t_Memory;  // address to value
	typedef list<int> t_List;

	class IntcodeVM
	{
	public:
		enum class State { empty, ready, running, wait_for_input, output_ready, halted };

		static t_Memory parse(const string& input);
		
		IntcodeVM();
		void load(const t_Memory& program);
		void reset();
		void patch(int address, int value);
		void add_input(int value);
		int get_input();
		int get_output();
		void run();
		int mem(int address);
		State state() const;

	private:
		int _ip;
		State _state;
		t_Memory _memory;
		t_List _input;
		t_List _output;

		enum class Operation {
			addition = 1, multiplication = 2, get_input = 3, put_output = 4,
			jump_if_true = 5, jump_if_false = 6, less_than = 7, equals = 8, halt = 99
		};

		enum class Mode { position = 0, immediate = 1 };

		int fetch(Mode mode);
		void store(int value);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
