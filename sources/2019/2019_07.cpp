#include "2019_07.h"

namespace Day07_2019
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

	IntcodeVM::IntcodeVM()
	{
		_state = State::empty;
		reset();
	}

	void IntcodeVM::load(const t_Memory& program)
	{
		_memory = program;
		reset();
	}

	void IntcodeVM::reset()
	{
		_ip = 0;
		_state = State::ready;
		_input.clear();
		_output.clear();
	}

	void IntcodeVM::patch(int address, int value)
	{
		_memory[address] = value;
	}

	void IntcodeVM::add_input(int value)
	{
		_input.push_back(value);
	}

	int IntcodeVM::get_input()
	{
		int value = _input.front();
		_input.pop_front();
		return value;
	}

	int IntcodeVM::get_output()
	{
		int value = _output.front();
		_output.pop_front();
		return value;
	}

	void IntcodeVM::run()
	{
		if (_state == State::empty || _state == State::halted)
			return;

		_state = State::running;
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
					if (_input.size() == 0)
					{
						_state = State::wait_for_input;
						_ip--;
						return;
					}

					store(get_input());
					break;
				}

				case Operation::put_output:
				{
					_output.push_back(fetch(mode1));
					_state = State::output_ready;
					return;
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
					_state = State::halted;
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

	IntcodeVM::State IntcodeVM::state() const
	{
		return _state;
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
		vector<int> phase(5);
		for (int i = 0; i < 5; i++)
			phase[i] = i;

		IntcodeVM vm;
		vm.load(program);
		int max_thruster = 0;
		do
		{
			int output = 0;
			for (auto p : phase)
			{
				vm.reset();
				vm.add_input(p);
				vm.add_input(output);
				vm.run();
				output = vm.get_output();
			}

			max_thruster = max(max_thruster, output);

		} while (next_permutation(phase.begin(), phase.end()));

		return max_thruster;
	}

	int part_two(const t_Memory& program)
	{
		vector<int> phase(5);
		for (int i = 0; i < 5; i++)
			phase[i] = i + 5;

		int max_thruster = 0;
		do
		{
			IntcodeVM amp[5];
			for (int p = 0; p < 5; p++)
			{
				amp[p].load(program);
				amp[p].add_input(phase[p]);
			}
			amp[0].add_input(0);

			int p = 0;
			int done = 0;
			while (done < 5)
			{
				amp[p].run();
				IntcodeVM::State state = amp[p].state();
				int next = (p + 1) % 5;

				switch (state)
				{
					case IntcodeVM::State::output_ready:
						amp[next].add_input(amp[p].get_output());
						break;

					case IntcodeVM::State::halted:
						done++;
						break;

					default:
						throw runtime_error("unsupported state");
						break;
				}

				p = next;
			}

			int output = amp[p].get_input();
			max_thruster = max(max_thruster, output);

		} while (next_permutation(phase.begin(), phase.end()));

		return max_thruster;
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
