#ifndef __2019_11__
#define __2019_11__

#include "../shared/Solution.h"

namespace Day11_2019
{
	// Intcode Virtual Machine version 5
	//
	// added in version 5 (2019/11):
	// - ability to check number of elements on output list
	//
	// added in version 4 (2019/09):
	// - switch params/addresses to signed 64-bit integer (from signed 32-bit integer)
	// - option to stop executing on producing output
	// - introducing adjust_relative_base instruction
	// - relative mode support on loads from memory and stores to the memory
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

	typedef map<int64_t, int64_t> t_Memory;  // address to value
	typedef list<int64_t> t_List;

	class IntcodeVM
	{
	public:
		enum class State { empty, ready, running, wait_for_input, output_ready, halted };

		static t_Memory parse(const string& input);

		IntcodeVM(bool stop_on_output);
		void load(const t_Memory& program);
		void reset();
		void patch(int64_t address, int64_t value);
		void add_input(int64_t value);
		int64_t get_input();
		int64_t get_output();
		size_t outputs_count();
		void run();
		int64_t mem(int64_t address);
		State state() const;

	private:
		bool _stop_on_output;
		State _state;
		int64_t _ip;
		int64_t _rel_base;
		t_Memory _memory;
		t_List _input;
		t_List _output;

		enum class Operation {
			addition = 1, multiplication = 2, get_input = 3, put_output = 4,
			jump_if_true = 5, jump_if_false = 6, less_than = 7, equals = 8, adjust_relative_base = 9, halt = 99
		};

		enum class Mode { position = 0, immediate = 1, relative = 2 };

		int64_t fetch(Mode mode);
		void store(int64_t value, Mode mode);
	};

	class Position
	{
	public:
		Position();
		Position(int x, int y);

		bool operator < (const Position& other) const;
		bool operator != (const Position& other) const;

		int x;
		int y;
	};

	class Features
	{
	public:
		Features();
		Features(int color);

		int color;	// 0 = black
		bool painted;
	};

	typedef std::map<Position, Features> t_mapArea;

	class Robot
	{
	public:
		Robot();

		void turn(int direction);
		void forward();

		Position position;
		int orientation;		// 0 = up, 1 = 90 deg, 2 = down, 3 = 270 deg
	};

	class RegistrationIdentifier
	{
	public:
		void paint(const t_Memory& program, int color);
		int painted_count();
		vector<string> plate();

	private:
		t_mapArea _area;

		void add_panel_if_missing(const Position& position);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
