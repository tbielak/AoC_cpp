#include "2019_11.h"

namespace Day11_2019
{
	t_Memory IntcodeVM::parse(const string& input)
	{
		intmax_t addr = 0;
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

	void IntcodeVM::patch(intmax_t address, intmax_t value)
	{
		_memory[address] = value;
	}

	void IntcodeVM::add_input(intmax_t value)
	{
		_input.push_back(value);
	}

	intmax_t IntcodeVM::get_input()
	{
		intmax_t value = _input.front();
		_input.pop_front();
		return value;
	}

	intmax_t IntcodeVM::get_output()
	{
		intmax_t value = _output.front();
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
			intmax_t param = _memory[_ip++] / 100;
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
					intmax_t src = fetch(mode1);
					intmax_t target = fetch(mode2);
					if (src != 0)
						_ip = target;

					break;
				}

				case Operation::jump_if_false:
				{
					intmax_t src = fetch(mode1);
					intmax_t target = fetch(mode2);
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

	intmax_t IntcodeVM::mem(intmax_t address)
	{
		return _memory[address];
	}

	IntcodeVM::State IntcodeVM::state() const
	{
		return _state;
	}

	intmax_t IntcodeVM::fetch(Mode mode)
	{
		intmax_t value = 0;
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

	void IntcodeVM::store(intmax_t value, Mode mode)
	{
		switch (mode)
		{
			case Mode::position: { _memory[_memory[_ip]] = value; break; }
			case Mode::relative: { _memory[_memory[_ip] + _rel_base] = value; break; }
			default: throw runtime_error("unsupported mode");
		}

		_ip++;
	}

	Position::Position()
	:	x(0), y(0)
	{
	}

	Position::Position(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Position::operator < (const Position& other) const
	{
		if (y == other.y)
			return x < other.x;

		return y < other.y;
	}

	bool Position::operator != (const Position& other) const
	{
		return (x == other.x && y == other.y) ? false : true;
	}

	Features::Features()
	:	color(0), painted(false)
	{
	}

	Features::Features(int color)
	:	color(color), painted(true)
	{
	}

	Robot::Robot()
	:	orientation(0)
	{
	}

	void Robot::turn(int direction)
	{
		if (direction == 0)
			orientation--;
		else
			orientation++;

		orientation &= 3;
	}

	void Robot::forward()
	{
		switch (orientation)
		{
			case 0: position.y--; break;
			case 1: position.x++; break;
			case 2: position.y++; break;
			case 3: position.x--; break;
		}
	}

	void RegistrationIdentifier::paint(const t_Memory& program, int color)
	{
		Robot robot;
		_area.clear();
		add_panel_if_missing(robot.position);

		IntcodeVM brain(true);
		brain.load(program);
		brain.add_input(color);
		while (brain.state() != IntcodeVM::State::halted)
		{
			brain.run();
			if (brain.state() == IntcodeVM::State::output_ready && brain.outputs_count() == 2)
			{
				int color = (int)brain.get_output();
				int direction = (int)brain.get_output();
				_area[robot.position] = Features(color);
				robot.turn(direction);
				robot.forward();
				add_panel_if_missing(robot.position);
				brain.add_input(_area[robot.position].color);
			}
		}
	}

	size_t RegistrationIdentifier::painted_count()
	{
		return count_if(_area.begin(), _area.end(), [](const auto& x) { return x.second.painted; });
	}

	vector<string> RegistrationIdentifier::plate()
	{
		int min_x = INT_MAX;
		int min_y = INT_MAX;
		int max_x = INT_MIN;
		int max_y = INT_MIN;
		for (auto& panel : _area)
		{
			min_x = min(min_x, panel.first.x);
			max_x = max(max_x, panel.first.x);
			min_y = min(min_y, panel.first.y);
			max_y = max(max_y, panel.first.y);
		}

		string s(max_x - min_x + 1, ' ');
		vector<string> result(max_y - min_y + 1, s);
		for (auto& panel : _area)
			if (panel.second.color == 1)
				result[panel.first.y][panel.first.x] = -37;

		return result;
	}

	void RegistrationIdentifier::add_panel_if_missing(const Position& position)
	{
		auto it = _area.find(position);
		if (it == _area.end())
			_area[position] = Features();
	}

	size_t part_one(RegistrationIdentifier& regid, const t_Memory& program)
	{
		regid.paint(program, 0);
		return regid.painted_count();
	}

	vector<string> part_two(RegistrationIdentifier& regid, const t_Memory& program)
	{
		regid.paint(program, 1);
		return regid.plate();
	}

	t_output main(const t_input& input)
	{
		auto program = IntcodeVM::parse(input[0]);

		RegistrationIdentifier regid;
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(regid, program);
		auto p2 = part_two(regid, program);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.insert(solutions.end(), p2.begin(), p2.end());
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
