#include "2019_05.h"

namespace Day05_2019
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

	void IntcodeVM::add_input(int value)
	{
		_input.push_back(value);
	}

	int IntcodeVM::get_output()
	{
		int value = _output.front();
		_output.pop_front();
		return value;
	}

	void IntcodeVM::run()
	{
		while (1)
		{
			Operation op = (Operation)(_memory[_ip] % 100);
			int param = _memory[_ip++] / 100;
			Mode mode1 = (Mode)(param % 10); param /= 10;
			Mode mode2 = (Mode)(param % 10); param /= 10;

			switch (op)
			{
				case Operation::addition:
				{
					store(fetch(mode1) + fetch(mode2));
					break;
				}

				case Operation::multiplication:
				{
					store(fetch(mode1) * fetch(mode2));
					break;
				}

				case Operation::get_input:
				{
					int value = _input.front();
					_input.pop_front();
					store(value);
					break;
				}

				case Operation::put_output:
				{
					_output.push_back(fetch(mode1));
					break;
				}

				case Operation::jump_if_true:
				{
					int src = fetch(mode1);
					int target = fetch(mode2);
					if (src != 0)
						_ip = target;

					break;
				}

				case Operation::jump_if_false:
				{
					int src = fetch(mode1);
					int target = fetch(mode2);
					if (src == 0)
						_ip = target;

					break;
				}

				case Operation::less_than:
				{
					store((fetch(mode1) < fetch(mode2)) ? 1 : 0);
					break;
				}

				case Operation::equals:
				{
					store((fetch(mode1) == fetch(mode2)) ? 1 : 0);
					break;
				}

				case Operation::halt:
					return;

				default:
					throw runtime_error("unsupported operation");
			}
		}
	}

	int IntcodeVM::mem(int address)
	{
		return _memory[address];
	}

	int IntcodeVM::fetch(Mode mode)
	{
		int value = 0;
		switch (mode)
		{
			case Mode::position: { value = _memory[_memory[_ip]]; break; }
			case Mode::immediate: { value = _memory[_ip]; break; }
			default: throw runtime_error("unsupported mode");
		}

		_ip++;
		return value;
	}

	void IntcodeVM::store(int value)
	{
		_memory[_memory[_ip++]] = value;
	}

	int part_one(const t_Memory& program)
	{
		IntcodeVM vm(program);
		vm.add_input(1);
		vm.run();

		int value = 0;
		while (value == 0)
			value = vm.get_output();

		return value;
	}

	int part_two(const t_Memory& program)
	{
		IntcodeVM vm(program);
		vm.add_input(5);
		vm.run();
		return vm.get_output();
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
