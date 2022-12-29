#include "2022_24.h"

namespace Day24_2022
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	
	State::State(const Point& p, const t_map& m, int steps /* = 0 */, uint8_t phase /* = 0 */)
	:	p(p), m(m), steps(steps), phase(phase)
	{
	}

	Solver::Solver(const vector<string>& input)
	{
		_height = (int)input.size();
		_width = (int)input[0].size();
		t_map bl = t_map(_height, t_row(_width, 0));

		static map<char, uint8_t> match = { {'^', 1}, {'v', 2}, {'<', 4}, {'>', 8} };
		for (int y = 1; y < _height - 1; y++)
			for (int x = 1; x < _width - 1; x++)
			{
				auto it = match.find(input[y][x]);
				if (it != match.end())
					bl[y][x] = it->second;
			}

		_start = Point(1, 0);
		_end = Point(_width - 2, _height - 1);
		_q.push(State(_start, bl));
	}

	int Solver::execute(int target_phase)
	{
		size_t last_phase = 0;
		while (_q.size() > 0)
		{
			auto [p, curr, steps, phase] = _q.front();
			_q.pop();

			if (p == _start)
			{
				if ((phase & 1) == 0)
					phase++;
			}
			else
				if (p == _end)
				{
					if ((phase & 1) == 1)
						phase++;
				}

			if (last_phase > phase)
				continue;

			last_phase = phase;
			if (phase == target_phase)
				return steps;

			t_map next = blizzard(curr, steps);
			if (valid(p, steps, next))
			{
				_visited.insert(make_pair(steps, p));
				_q.push(State(p, next, steps + 1, phase));
			}

			static vector<Point> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
			for (int i = 0; i < 4; i++)
			{
				Point n(p.x + directions[i].x, p.y + directions[i].y);
				if (valid(n, steps, next))
				{
					_visited.insert(make_pair(steps, n));
					_q.push(State(n, next, steps + 1, phase));
				}
			}
		}

		return -1;
	}

	void Solver::do_move(t_map& dst, const t_map& src) const
	{
		dst = t_map(_height, t_row(_width, 0));
		for (int y = 1; y < _height - 1; y++)
			for (int x = 1; x < _width - 1; x++)
			{
				uint8_t v = src[y][x];

				if ((v & 1) > 0)	// up
				{
					int ny = (y > 1) ? y - 1 : _height - 2;
					dst[ny][x] |= uint8_t(1);
				}

				if ((v & 2) > 0)	// down
				{
					int ny = (y < _height - 2 ? y + 1 : 1);
					dst[ny][x] |= uint8_t(2);
				}

				if ((v & 4) > 0)	// left
				{
					int nx = (x > 1) ? x - 1 : _width - 2;
					dst[y][nx] |= uint8_t(4);
				}

				if ((v & 8) > 0)	// right
				{
					int nx = (x < _width - 2 ? x + 1 : 1);
					dst[y][nx] |= uint8_t(8);
				}
			}
	}

	t_map Solver::blizzard(const t_map& curr, int steps)
	{
		t_map next;
		auto it = _cache.find(steps);
		if (it != _cache.end())
			next = it->second;
		else
		{
			do_move(next, curr);
			_cache[steps] = next;
		}

		return next;
	}

	bool Solver::valid(const Point& p, int steps, const t_map& next) const
	{
		if (_visited.find(make_pair(steps, p)) != _visited.end())
			return false;

		if (p == _start || p == _end)
			return true;

		if (p.x > 0 && p.x < _width - 1 && p.y > 0 && p.y < _height - 1 && next[p.y][p.x] == 0)
			return true;

		return false;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver(input).execute(2);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Solver(input).execute(4);
	}
}
