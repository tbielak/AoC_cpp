#include "2019_02.h"

namespace Day02_2019
{
	t_Memory IntcodeVM::parse(const string& input)
	{
		int addr = 0;
		t_Memory m;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			m[addr++] = stoi(s);

		return m;
	}

	IntcodeVM::IntcodeVM(const t_Memory& program)
	:	_ip(0)
	{
		_memory = program;
	}

	void IntcodeVM::patch(int address, int value)
	{
		_memory[address] = value;
	}

	void IntcodeVM::run()
	{
		while (1)
		{
			Operation op = (Operation)_memory[_ip++];
			switch (op)
			{
				case Operation::addition:		{ store(fetch() + fetch()); break; }
				case Operation::multiplication:	{ store(fetch() * fetch()); break; }
				case Operation::halt:			return;
				default:						throw runtime_error("unsupported operation");
			}
		}
	}

	int IntcodeVM::mem(int address)
	{
		return _memory[address];
	}

	int IntcodeVM::fetch()
	{
		return _memory[_memory[_ip++]];
	}

	void IntcodeVM::store(int v)
	{
		_memory[_memory[_ip++]] = v;
	}

	int part_one(const t_Memory& program)
	{
		IntcodeVM vm(program);
		vm.patch(1, 12);
		vm.patch(2, 2);
		vm.run();
		return vm.mem(0);
	}

	int part_two(const t_Memory& program)
	{
		for (int noun = 0; noun <= 100; noun++)
			for (int verb = 0; verb <= 100; verb++)
			{
				IntcodeVM vm(program);
				vm.patch(1, noun);
				vm.patch(2, verb);
				vm.run();
				if (19690720 == vm.mem(0))
					return 100 * noun + verb;
			}

		return -1;
	}

	t_output main(const t_input& input)
	{
		auto program = IntcodeVM::parse(input[0]);

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(program);
		auto p2 = part_two(program);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
