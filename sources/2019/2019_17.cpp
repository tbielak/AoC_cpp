#include "2019_17.h"

namespace Day17_2019
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

	Position::Position(int row /* = 0 */, int col /* = 0 */)
		: row(row), col(col)
	{
	}

	bool Position::operator < (const Position& other) const
	{
		if (row == other.row)
			return col < other.col;

		return row < other.row;
	}

	Serie::Serie(const string& s)
	:	s(s), c(0)
	{
	}

	void Serie::count(const string& path)
	{
		for (size_t i = 0; i < path.size(); i++)
			if (path.substr(i, s.size()) == s)
				c++;
	}

	bool Serie::order(const Serie& x, const Serie& y)
	{
		return x.c > y.c;
	}

	Scaffold::Scaffold(const t_Memory& program)
	{
		// create scaffold (IntCode output) rounded by '.' (no boundaries checking later)
		string line = ".";
		_view.push_back(line);

		_width = 0;
		IntcodeVM vm(true);
		vm.load(program);
		while (vm.state() != IntcodeVM::State::halted)
		{
			vm.run();
			if (vm.state() == IntcodeVM::State::output_ready)
			{
				char ch = (char)vm.get_output();
				if (ch != 10)
					line += ch;
				else
				{
					line += ".";
					_view.push_back(line);
					if (_width == 0)
						_width = (int)line.size();
					line = ".";
				}
			}
		}

		// update first and last line
		line = string(_width, '.');
		_view[0] = line;
		_view.back() = line;

		// scan scaffold
		_height = (int)_view.size();
		for (int row = 1; row <= _height - 1; row++)
			for (int col = 1; col <= _width - 1; col++)
			{
				// find crossings
				if (_view[row][col] == '#' &&
					_view[row - 1][col] == '#' && _view[row + 1][col] == '#' &&
					_view[row][col - 1] == '#' && _view[row][col + 1] == '#')
					_crossings.insert(Position(row, col));

				// find robot
				if (_view[row][col] == '^')
					_robot = Position(row, col);
			}
	}

	int Scaffold::sum_of_alignment_parameters() const
	{
		int sum = 0;
		for (const auto& c : _crossings)
			sum += (c.row - 1) * (c.col - 1);

		return sum;
	}

	int64_t Scaffold::collect_dust(const t_Memory& program)
	{
		if (!create_commands())
			return -1; // something unexpected happened

		create_series();
		build_routine();
		
		IntcodeVM collector(true);
		collector.load(program);
		collector.patch(0, 2);

		size_t idx = 0;
		int64_t dust = -1;
		while (collector.state() != IntcodeVM::State::halted)
		{
			collector.run();
			if (collector.state() == IntcodeVM::State::wait_for_input)
				collector.add_input(_routine[idx++]);

			if (collector.state() == IntcodeVM::State::output_ready)
				dust = collector.get_output();
		}

		return dust;
	}

	bool Scaffold::create_commands()
	{
		int dir = 0;	// direction:	0 ^	1 <	2 v	3 >
		string cmd;

		int rrow = _robot.row;
		int rcol = _robot.col;
		while (1)
		{
			int steps = 0;
			while (1)
			{
				// can robot move in desired direction?
				if (_view[rrow + _directions[dir].row][rcol + _directions[dir].col] != '#')
					break;

				// count step, block returning by removing scaffold (when no crossing)
				steps++;
				if (_crossings.find(Position(rrow, rcol)) == _crossings.end())
					_view[rrow][rcol] = '.';

				// make move
				rrow += _directions[dir].row;
				rcol += _directions[dir].col;
			}

			// any steps? make command, update full path
			if (steps > 0)
			{
				_commands.push_back(cmd + "," + to_string(steps));
				_fullpath += cmd + "," + to_string(steps) + ",";
			}

			// find new direction
			int ndir = -1;
			if (dir != 0 && _view[rrow - 1][rcol] == '#') ndir = 0;
			if (dir != 1 && _view[rrow][rcol - 1] == '#') ndir = 1;
			if (dir != 2 && _view[rrow + 1][rcol] == '#') ndir = 2;
			if (dir != 3 && _view[rrow][rcol + 1] == '#') ndir = 3;

			// no other way?
			if (ndir == -1)
				break;

			// assign command
			if (dir == 0 && ndir == 1) cmd = "L"; else
			if (dir == 1 && ndir == 2) cmd = "L"; else
			if (dir == 2 && ndir == 3) cmd = "L"; else
			if (dir == 3 && ndir == 0) cmd = "L"; else
			if (dir == 0 && ndir == 3) cmd = "R"; else
			if (dir == 3 && ndir == 2) cmd = "R"; else
			if (dir == 2 && ndir == 1) cmd = "R"; else
			if (dir == 1 && ndir == 0) cmd = "R"; else
				return false;

			dir = ndir;
		}

		return true;
	}

	void Scaffold::create_series()
	{
		set<string> ss;
		for (size_t how_many = 2; how_many < _commands.size() / 6; how_many++)
		{
			for (size_t i = 0; i < _commands.size() - how_many + 1; i++)
			{
				string s;
				for (size_t j = 0; j < how_many; j++)
					s += _commands[i + j] + ",";

				ss.insert(s);
			}
		}

		for (const auto& s : ss)
			_series.push_back(s);

		for (size_t i = 0; i < _series.size(); i++)
			_series[i].count(_fullpath);

		stable_sort(_series.begin(), _series.end(), Serie::order);
	}

	void Scaffold::build_routine()
	{
		for (size_t i = 0; i < _series.size(); i++)
			recursive_build_routine("A", _fullpath, i);
	}

	void Scaffold::recursive_build_routine(const string& routine, const string& path, size_t idx)
	{
		// single comment for this whole method: just some ugly string operations ;)

		if (_routine != "")	// needed one solution only (single routine is enough)
			return;

		string s = path;
		_map[routine[0]] = _series[idx].s;
		for (size_t i = 0; i < _series[idx].c; i++)
		{
			size_t pos = s.find(_series[idx].s);
			if (pos != string::npos)
			{
				s.erase(pos, _series[idx].s.size() - 1);
				s.insert(pos, routine);
			}
		}

		string new_routine = routine;
		(new_routine[0])++;
		if (new_routine[0] == 'D')
		{
			bool ok = true;
			for (auto c : s)
				if (c == 'L' || c == 'R')
					ok = false;

			if (ok)
			{
				for (const auto& m : _map)
					if (m.second.size() >= _vacuum_robot_limit + 2)
						ok = false;
			}

			if (ok)
			{
				// one of available solutions
				_routine = s;
				_routine.back() = 10;
				
				for (const auto& m : _map)
				{
					_routine += m.second;
					_routine.back() = 10;
				}

				// no video feed
				_routine += "nn";
				_routine.back() = 10;
			}

			return;
		}

		for (size_t i = 0; i < _series.size(); i++)
			recursive_build_routine(new_routine, s, i);
	}

	AoC::Output Main::part_one(const string& input)
	{
		auto program = IntcodeVM::parse(input);
		return Scaffold(program).sum_of_alignment_parameters();
	}

	AoC::Output Main::part_two(const string& input)
	{
		auto program = IntcodeVM::parse(input);
		return Scaffold(program).collect_dust(program);
	}
}
