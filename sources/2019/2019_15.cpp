#include "2019_15.h"

namespace Day15_2019
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

	State::State(const IntcodeVM& droid, int x, int y, int direction)
	:	droid(droid), x(x), y(y), direction(direction)
	{
	}

	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	Labyrinth::Labyrinth(const t_Memory& program)
	:	_droid(true), _ox(0), _oy(0)
	{
		_droid.load(program);

		int x = 0;
		int y = 0;
		int mask = 0;
		_area[x][y] = '.';
		int current_state = -1;
		t_vecState state;

		while (1)
		{
			int direction = 0;
			string result = probe(x, y, mask);

			if (result.size() == 0)
			{
				current_state++;
				if (current_state == (int)state.size())
					break;

				x = state[current_state].x;
				y = state[current_state].y;
				direction = state[current_state].direction;
				_droid = state[current_state].droid;
			}
			else
			{
				for (size_t i = 1; i < result.size(); i++)
					state.push_back(State(_droid, x, y, result[i] - '0'));

				direction = result[0] - '0';
			}

			update_position(x, y, direction);
			move_droid(direction);
			mask = opposite_direction(direction);
		}
	}

	void Labyrinth::shortest_recursive(int x, int y, int block, int count, int& result) const
	{
		if (x == _ox && y == _oy)
		{
			if (result > count)
				result = count;
		}

		if (peek(x - 1, y) == '.' && block != 1)
			shortest_recursive(x - 1, y, 2, count + 1, result);

		if (peek(x + 1, y) == '.' && block != 2)
			shortest_recursive(x + 1, y, 1, count + 1, result);

		if (peek(x, y - 1) == '.' && block != 3)
			shortest_recursive(x, y - 1, 4, count + 1, result);

		if (peek(x, y + 1) == '.' && block != 4)
			shortest_recursive(x, y + 1, 3, count + 1, result);
	}

	int Labyrinth::oxygen_fill_minutes()
	{
		int minutes = 1;
		t_vecPoint o2;
		o2.push_back(Point(_ox, _oy));

		size_t dots_left = count_dots();
		while (dots_left > 0)
		{
			minutes++;
			t_vecPoint n;
			for (const auto p : o2)
				spread_oxygen(dots_left, n, p);

			o2 = n;
		}

		return minutes;
	}

	string Labyrinth::probe(int x, int y, int mask)
	{
		string result;
		for (int direction = 1; direction <= 4; direction++)	// 1 = north, 2 = south, 3 = west, 4 = east
		{
			int nx = x;
			int ny = y;
			int back = 0;
			do
			{
				_droid.run();
				if (_droid.state() == IntcodeVM::State::wait_for_input)
				{
					if (back > 0)
						_droid.add_input(back);
					else
					{
						back = 0;
						_droid.add_input(direction);
						update_position(nx, ny, direction);
					}
				}

				if (_droid.state() == IntcodeVM::State::output_ready)
				{
					int out = (int)_droid.get_output();
					if (back == 0)
					{
						if (out == 0)
						{
							_area[nx][ny] = '#';
							back = 15;
						}
						if (out > 0)
						{
							if (direction != mask)
								result += char(direction + '0');
							
							_area[nx][ny] = '.';
							back = opposite_direction(direction);

							if (out == 2)
							{
								_ox = x;
								_oy = y;
							}
						}
					}
					else
						back = 15;
				}
			} while (back != 15);
		}

		return result;
	}

	void Labyrinth::move_droid(int direction)
	{
		while (1)
		{
			_droid.run();
			if (_droid.state() == IntcodeVM::State::wait_for_input)
				_droid.add_input(direction);

			if (_droid.state() == IntcodeVM::State::output_ready)
			{
				_droid.get_output();
				break;
			}
		}
	}

	int Labyrinth::opposite_direction(int direction) const
	{
		return ((direction - 1) ^ 1) + 1;
	}

	void Labyrinth::update_position(int& x, int& y, int direction)
	{
		switch (direction)
		{
			case 1: y--; break;
			case 2: y++; break;
			case 3: x--; break;
			case 4: x++; break;
		}
	}

	char Labyrinth::peek(int x, int y) const
	{
		t_area::const_iterator it = _area.find(x);
		if (it == _area.end())
			return ' ';

		t_col::const_iterator cit = it->second.find(y);
		return (cit == it->second.end()) ? ' ' : cit->second;
	}

	size_t Labyrinth::count_dots() const
	{
		size_t n = 0;
		for (const auto col : _area)
			n += count_if(col.second.begin(), col.second.end(), [](const auto& x) { return x.second == '.'; });

		return n;
	}

	void Labyrinth::spread_oxygen(size_t& dots_left, t_vecPoint& n, int x, int y)
	{
		if (peek(x, y) == '.')
			dots_left--;

		_area[x][y] = 'O';
		n.push_back(Point(x, y));
	}

	void Labyrinth::spread_oxygen(size_t& dots_left, t_vecPoint& n, const Point& p)
	{
		if (peek(p.x - 1, p.y) == '.') spread_oxygen(dots_left, n, p.x - 1, p.y);
		if (peek(p.x + 1, p.y) == '.') spread_oxygen(dots_left, n, p.x + 1, p.y);
		if (peek(p.x, p.y - 1) == '.') spread_oxygen(dots_left, n, p.x, p.y - 1);
		if (peek(p.x, p.y + 1) == '.') spread_oxygen(dots_left, n, p.x, p.y + 1);
	}

	AoC::Output Main::part_one(const string& input)
	{
		int result = INT_MAX;
		Labyrinth(IntcodeVM::parse(input)).shortest_recursive(0, 0, 0, 0, result);
		return result + 1;
	}

	AoC::Output Main::part_two(const string& input)
	{
		return Labyrinth(IntcodeVM::parse(input)).oxygen_fill_minutes();
	}
}
