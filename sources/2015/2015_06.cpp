#include "2015_06.h"

namespace Day06_2015
{
	Instruction::Instruction(const string& s, const t_point& from, const t_point& to)
	:	from(from), to(to)
	{
		if ("turn on" == s) cmd = Command::turn_on;
		else if ("turn off" == s) cmd = Command::turn_off;
		else cmd = Command::toggle;
	}

	Grid::Grid()
	{
		vector<int> x(1000);
		_lights = vector<vector<int>>(1000, x);
	}
	
	void Grid::set(const t_point& from, const t_point& to, int v)
	{
		for (int y = from.second; y <= to.second; y++)
			for (int x = from.first; x <= to.first; x++)
				_lights[y][x] = v;
	}

	void Grid::toggle(const t_point& from, const t_point& to)
	{
		for (int y = from.second; y <= to.second; y++)
			for (int x = from.first; x <= to.first; x++)
				_lights[y][x] ^= 1;
	}

	void Grid::add(const t_point& from, const t_point& to, int v)
	{
		for (int y = from.second; y <= to.second; y++)
			for (int x = from.first; x <= to.first; x++)
				_lights[y][x] += v;
	}

	void Grid::dec(const t_point& from, const t_point& to)
	{
		for (int y = from.second; y <= to.second; y++)
			for (int x = from.first; x <= to.first; x++)
				if (_lights[y][x] > 0)
					_lights[y][x]--;
	}

	int Grid::sum()
	{
		return accumulate(_lights.cbegin(), _lights.cend(), 0,
			[](auto v, const auto& i) { return accumulate(i.cbegin(), i.cend(), v); });
	}

	t_vecInstruction Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("(turn on|turn off|toggle) ([0-9]*),([0-9]*) through ([0-9]*),([0-9]*)");
		t_vecInstruction instructions;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			instructions.push_back(Instruction(
				matches[1].str(),
				make_pair(stoi(matches[2].str()), stoi(matches[3].str())),
				make_pair(stoi(matches[4].str()), stoi(matches[5].str()))));
		}
		
		return instructions;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_vecInstruction instructions = load(input);

		Grid g;
		for (const auto& i : instructions)
		{
			switch (i.cmd)
			{
				case Command::turn_on: g.set(i.from, i.to, 1); break;
				case Command::turn_off: g.set(i.from, i.to, 0); break;
				default: g.toggle(i.from, i.to); break;
			}
		}

		return g.sum();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_vecInstruction instructions = load(input);

		Grid g;
		for (const auto& i : instructions)
		{
			switch (i.cmd)
			{
				case Command::turn_on: g.add(i.from, i.to, 1); break;
				case Command::turn_off: g.dec(i.from, i.to); break;
				default: g.add(i.from, i.to, 2); break;
			}
		}

		return g.sum();
	}
}
