#include "2019_13.h"

namespace Day13_2019
{
	t_Memory IntcodeVM::parse(const string& input)
	{
		int64_t addr = 0;
		t_Memory m;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			m[addr++] = stoll(s);

		return m;
	}

	IntcodeVM::IntcodeVM(bool stop_on_output)
	:	_stop_on_output(stop_on_output), _state(State::empty)
	{
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
		_rel_base = 0;
		_state = State::ready;
		_input.clear();
		_output.clear();
	}

	void IntcodeVM::patch(int64_t address, int64_t value)
	{
		_memory[address] = value;
	}

	void IntcodeVM::add_input(int64_t value)
	{
		_input.push_back(value);
	}

	int64_t IntcodeVM::get_input()
	{
		int64_t value = _input.front();
		_input.pop_front();
		return value;
	}

	int64_t IntcodeVM::get_output()
	{
		int64_t value = _output.front();
		_output.pop_front();
		return value;
	}

	size_t IntcodeVM::outputs_count()
	{
		return _output.size();
	}

	void IntcodeVM::run()
	{
		if (_state == State::empty || _state == State::halted)
			return;

		_state = State::running;
		while (1)
		{
			Operation op = (Operation)(_memory[_ip] % 100);
			int64_t param = _memory[_ip++] / 100;
			Mode mode1 = (Mode)(param % 10); param /= 10;
			Mode mode2 = (Mode)(param % 10); param /= 10;
			Mode mode3 = (Mode)(param % 10);

			switch (op)
			{
				case Operation::addition:
				{
					store(fetch(mode1) + fetch(mode2), mode3);
					break;
				}

				case Operation::multiplication:
				{
					store(fetch(mode1) * fetch(mode2), mode3);
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

					store(get_input(), mode1);
					break;
				}

				case Operation::put_output:
				{
					_output.push_back(fetch(mode1));
					if (_stop_on_output)
					{
						_state = State::output_ready;
						return;
					}

					break;
				}

				case Operation::jump_if_true:
				{
					int64_t src = fetch(mode1);
					int64_t target = fetch(mode2);
					if (src != 0)
						_ip = target;

					break;
				}

				case Operation::jump_if_false:
				{
					int64_t src = fetch(mode1);
					int64_t target = fetch(mode2);
					if (src == 0)
						_ip = target;

					break;
				}

				case Operation::less_than:
				{
					store((fetch(mode1) < fetch(mode2)) ? 1 : 0, mode3);
					break;
				}

				case Operation::equals:
				{
					store((fetch(mode1) == fetch(mode2)) ? 1 : 0, mode3);
					break;
				}

				case Operation::adjust_relative_base:
				{
					_rel_base += fetch(mode1);
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

	int64_t IntcodeVM::mem(int64_t address)
	{
		return _memory[address];
	}

	IntcodeVM::State IntcodeVM::state() const
	{
		return _state;
	}

	int64_t IntcodeVM::fetch(Mode mode)
	{
		int64_t value = 0;
		switch (mode)
		{
			case Mode::position: { value = _memory[_memory[_ip]]; break; }
			case Mode::immediate: { value = _memory[_ip]; break; }
			case Mode::relative: { value = _memory[_memory[_ip] + _rel_base]; break; }
			default: throw runtime_error("unsupported mode");
		}

		_ip++;
		return value;
	}

	void IntcodeVM::store(int64_t value, Mode mode)
	{
		switch (mode)
		{
			case Mode::position: { _memory[_memory[_ip]] = value; break; }
			case Mode::relative: { _memory[_memory[_ip] + _rel_base] = value; break; }
			default: throw runtime_error("unsupported mode");
		}

		_ip++;
	}

	int Main::isgn(int x)
	{
		return (0 < x) - (x < 0);
	}

	AoC::Output Main::part_one(const string& input)
	{
		IntcodeVM arcade(true);
		arcade.load(IntcodeVM::parse(input));

		int block_count = 0;
		while (arcade.state() != IntcodeVM::State::halted)
		{
			arcade.run();
			if (arcade.state() == IntcodeVM::State::output_ready && arcade.outputs_count() == 3)
			{
				arcade.get_output();
				arcade.get_output();
				int k = (int)arcade.get_output();

				if (k == 2)
					block_count++;
			}
		}

		return block_count;
	}

	AoC::Output Main::part_two(const string& input)
	{
		// board
		IntcodeVM arcade(true);
		arcade.load(IntcodeVM::parse(input));

		// insert 2 quarters to play for free :)
		arcade.patch(0, 2);

		int paddle_x = -1;
		int ball_x = -1;
		int score = 0;

		while (arcade.state() != IntcodeVM::State::halted)
		{
			arcade.run();
			if (arcade.state() == IntcodeVM::State::output_ready && arcade.outputs_count() == 3)
			{
				int x = (int)arcade.get_output();
				int y = (int)arcade.get_output();
				int k = (int)arcade.get_output();

				if (x == -1 && y == 0)
					score = k;
				else
				{
					if (k == 3) paddle_x = x;
					if (k == 4) ball_x = x;
				}
			}

			if (arcade.state() == IntcodeVM::State::wait_for_input)
				arcade.add_input(isgn(ball_x - paddle_x));		// integer signum of positions as joystick tilt
		}
		
		return score;
	}
}
