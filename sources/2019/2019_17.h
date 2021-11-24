#ifndef __2019_17__
#define __2019_17__

#include "../shared/input_output.h"

namespace Day17_2019
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

	typedef map<intmax_t, intmax_t> t_Memory;  // address to value
	typedef list<intmax_t> t_List;

	class IntcodeVM
	{
	public:
		enum class State { empty, ready, running, wait_for_input, output_ready, halted };

		static t_Memory parse(const string& input);

		IntcodeVM(bool stop_on_output);
		void load(const t_Memory& program);
		void reset();
		void patch(intmax_t address, intmax_t value);
		void add_input(intmax_t value);
		intmax_t get_input();
		intmax_t get_output();
		size_t outputs_count();
		void run();
		intmax_t mem(intmax_t address);
		State state() const;

	private:
		bool _stop_on_output;
		State _state;
		intmax_t _ip;
		intmax_t _rel_base;
		t_Memory _memory;
		t_List _input;
		t_List _output;

		enum class Operation {
			addition = 1, multiplication = 2, get_input = 3, put_output = 4,
			jump_if_true = 5, jump_if_false = 6, less_than = 7, equals = 8, adjust_relative_base = 9, halt = 99
		};

		enum class Mode { position = 0, immediate = 1, relative = 2 };

		intmax_t fetch(Mode mode);
		void store(intmax_t value, Mode mode);
	};

	class Position
	{
	public:
		Position(int row = 0, int col = 0);
		bool operator < (const Position& other) const;

		int row, col;
	};

	class Serie
	{
	public:
		Serie(const string& s);
		void count(const string& path);

		static bool order(const Serie& x, const Serie& y);

		string s;
		size_t c;
	};

	typedef vector<Serie> t_series;

	class Scaffold
	{
	public:
		Scaffold(const t_Memory& program);

		int sum_of_alignment_parameters() const;
		intmax_t collect_dust(const t_Memory& program);

	private:
		vector<string> _view;
		int _width, _height;
		Position _robot;
		set<Position> _crossings;
		vector<string> _commands;
		const vector<Position> _directions = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
		string _fullpath;
		t_series _series;

		typedef map<char, string> t_map;
		t_map _map;
		const size_t _vacuum_robot_limit = 20;
		t_Memory _program;
		string _routine;

		bool create_commands();
		void create_series();
		void build_paths();
		void recursive_build_routines(const string& level, const string& path, size_t idx);
	};

	t_output main(const t_input& input);
}

#endif
