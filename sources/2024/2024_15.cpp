#include "2024_15.h"

namespace Day15_2024
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	Point& Point::operator += (const Point& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point& Point::operator -= (const Point& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool Point::operator != (const Point& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	Warehouse::Warehouse(const vector<string>& input, bool expanded /* = false */)
	:	_expanded(expanded)
	{
		size_t i = 0;
		for (; !input[i].empty(); i++)
		{
			if (expanded)
			{
				_map.push_back(string());
				for (char c : input[i])
				{
					switch (c)
					{
					case '#': _map.back() += "##"; break;
					case 'O': _map.back() += "[]"; break;
					case '.': _map.back() += ".."; break;
					case '@': _map.back() += "@."; break;
					}
				}
			}
			else
				_map.push_back(input[i]);
		}

		for (i++; i < input.size(); i++)
			_moves += input[i];

		_width = (int)_map[0].size();
		_height = (int)_map.size();
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				if (_map[y][x] == '@')
				{
					_robot = Point(x, y);
					return;
				}
	}

	void Warehouse::move(const Point& d)
	{
		Point p(_robot.x + d.x, _robot.y + d.y);
		while (_map[p.y][p.x] != '.' && _map[p.y][p.x] != '#') p += d;
		if (_map[p.y][p.x] == '.')
		{
			for (; p != _robot; p -= d)
				_map[p.y][p.x] = _map[p.y - d.y][p.x - d.x];

			_map[_robot.y][_robot.x] = '.';
			_robot += d;
		}
	}

	void Warehouse::move_y(int dy)
	{
		stack<Point> m;
		m.push(_robot);

		queue<Point> q;
		q.push(_robot);

		while (q.size() > 0)
		{
			auto [x, y] = q.front();
			q.pop();

			y += dy;
			if (_map[y][x] == '#')
				return;

			if (_map[y][x] == '[' || _map[y][x] == ']')
			{
				if (_map[y][x] == ']')
					x--;

				m.push(Point(x, y));
				q.push(Point(x, y));
				m.push(Point(x + 1, y));
				q.push(Point(x + 1, y));
			}
		}

		set<Point> moved;
		while (m.size() > 0)
		{
			auto p = m.top();
			m.pop();

			auto it = moved.find(p);
			if (it == moved.end())
			{
				_map[p.y + dy][p.x] = _map[p.y][p.x];
				_map[p.y][p.x] = '.';
				moved.insert(p);
			}
		}

		_robot.y += dy;
	}

	Warehouse& Warehouse::go()
	{
		for (auto c : _moves)
		{
			switch (c)
			{
			case '>': move(Point(1, 0)); break;
			case '<': move(Point(-1, 0)); break;
			case 'v': if (_expanded) move_y(1); else move(Point(0, 1)); break;
			case '^': if (_expanded) move_y(-1); else move(Point(0, -1)); break;
			}
		}

		return *this;
	}

	int Warehouse::count(char c) const
	{
		int sum = 0;
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				if (_map[y][x] == c)
					sum += y * 100 + x;

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Warehouse(input).go().count('O');
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Warehouse(input, true).go().count('[');
	}
}
