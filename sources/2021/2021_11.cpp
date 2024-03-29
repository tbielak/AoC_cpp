#include "2021_11.h"

namespace Day11_2021
{
	Position::Position(int y, int x)
	:	y(y), x(x)
	{
	}

	bool Position::operator < (const Position& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	Octopuses::Octopuses(const vector<string>& input)
	:	_grid(input)
	{
		_size = (int)_grid.size();
	}

	int Octopuses::flashes_after(int steps)
	{
		int count = 0;
		for (int i = 0; i < steps; i++)
			count += step();
		
		return count;
	}

	int Octopuses::all_flashed()
	{
		int i = 1;
		for (; ; i++)
			if (step() == _size * _size)
				break;

		return i;
	}

	int Octopuses::step()
	{
		t_vecPosition pos;
		t_setPosition flash;
		for (int y = 0; y < _size; y++)
			for (int x = 0; x < _size; x++)
				increase_energy(pos, flash, Position(y, x));

		int idx = 0;
		while (idx < (int)pos.size())
		{
			Position p = pos[idx++];
			for (int y = p.y - 1; y <= p.y + 1; y++)
				for (int x = p.x - 1; x <= p.x + 1; x++)
					if (inside(y, x) && _grid[y][x] <= '9')
						increase_energy(pos, flash, Position(y, x));
		}

		for (const auto& p : flash)
			_grid[p.y][p.x] = '0';

		return (int)flash.size();
	}

	void Octopuses::increase_energy(t_vecPosition& pos, t_setPosition& flash, const Position& p)
	{
		_grid[p.y][p.x]++;
		if (_grid[p.y][p.x] > '9' && flash.find(p) == flash.end())
		{
			pos.push_back(p);
			flash.insert(p);
		}
	}

	bool Octopuses::inside(int y, int x)
	{
		return y >= 0 && y < _size && x >= 0 && x < _size;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Octopuses(input).flashes_after(100);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Octopuses(input).all_flashed();
	}
}
