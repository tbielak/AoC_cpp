#include "2018_20.h"

namespace Day20_2018
{
	Position::Position(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Position::operator < (const Position& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	Solver::Solver(const string& input)
	{
		vector<Node> stack;
		stack.push_back(_current);

		for (char c : input)
			switch (c)
			{
			case '(': stack.push_back(_current); break;
			case ')': _current = stack.back(); stack.pop_back(); break;
			case '|': _current = stack[stack.size() - 1]; break;
			case 'N': move(0, -1); break;
			case 'E': move(1, 0); break;
			case 'S': move(0, 1); break;
			case 'W': move(-1, 0); break;
			}
	}

	int Solver::longest_path() const
	{
		int len = 0;
		for (const auto& [_, dist] : _distances)
			len = max(len, dist);

		return len;
	}

	int Solver::at_least(int threshold) const
	{
		int count = 0;
		for (const auto& [_, dist] : _distances)
			if (dist >= threshold)
				count++;

		return count;
	}

	void Solver::move(int dx, int dy)
	{
		Position p(_current.pos.x + dx, _current.pos.y + dy);
		int d = _distances[p];
		d = (d == 0) ? _current.dist + 1 : min(d, _current.dist + 1);
		_distances[p] = d;
		_current.pos = p;
		_current.dist = d;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return Solver(input).longest_path();
	}

	AoC::Output Main::part_two(const string& input)
	{
		return Solver(input).at_least(1000);
	}
}
