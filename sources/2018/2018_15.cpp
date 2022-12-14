#include "2018_15.h"

namespace Day15_2018
{
	Point::Point(int x /* = -1 */, int y /* = -1 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Point::operator != (const Point& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	Path::Path()
	:	total_steps(0)
	{
	}

	Path::Path(const Point& target, const Point& next_step, int total_steps)
	:	target(target), next_step(next_step), total_steps(total_steps)
	{
	}

	bool Path::operator < (const Path& rhs) const
	{
		if (total_steps == rhs.total_steps)
		{
			if (target.y == rhs.target.y)
				return target.x < rhs.target.x;

			return target.y < rhs.target.y;
		}

		return total_steps < rhs.total_steps;
	}

	bool Path::empty() const
	{
		return total_steps == 0;
	}

	Unit::Unit(const Point& p, char type, int power)
	:	p(p), type(type), health(200), power(power)
	{
	}

	vector<int> Combat::_move_x = { 0, -1, 1, 0 };
	vector<int> Combat::_move_y = { -1, 0, 0, 1 };

	Combat::Combat(const vector<string>& input, int elf_power /* = 3 */)
	:	_area(input)
	{
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == 'G' || input[y][x] == 'E')
					_units.push_back(Unit(Point(x, y), input[y][x], input[y][x] == 'G' ? 3 : elf_power));
	}

	int Combat::run(bool fail_if_elf_dead /* = false */)
	{
		for (int rounds = 0; ; rounds++)
		{
			sort(_units.begin(), _units.end(), reading_order);

			for (int i = 0; i < (int)_units.size(); i++)
			{
				auto targets = find_targets(i);
				if (targets.size() == 0)
					return rounds * total_health();

				if (!any_adjacent(targets, i))
				{
					auto in_range = targets_in_range(targets);
					auto sections = find_sections(_units[i].p);
					auto path = find_path(_units[i].p, in_range, sections);

					if (!path.empty())
						_units[i].p = path.next_step;
				}

				auto adjacent = find_adjacent(targets, i);
				if (adjacent.size() == 0)
					continue;

				sort(adjacent.begin(), adjacent.end(), health_reading_order);
					
				adjacent[0]->health -= _units[i].power;
				if (adjacent[0]->health > 0)
					continue;

				if (fail_if_elf_dead && adjacent[0]->type == 'E')
					return -1;

				int idx = 0;
				while (_units[idx].health > 0)
					idx++;

				_units.erase(_units.begin() + idx);
				if (idx < i)
					i--;
			}
		}
	}

	bool Combat::reading_order(const Unit& me, const Unit& other)
	{
		if (me.p.y == other.p.y)
			return me.p.x < other.p.x;

		return me.p.y < other.p.y;
	}

	bool Combat::health_reading_order(const Unit* me, const Unit* other)
	{
		if (me->health == other->health)
		{
			if (me->p.y == other->p.y)
				return me->p.x < other->p.x;

			return me->p.y < other->p.y;
		}

		return me->health < other->health;
	}

	int Combat::total_health() const
	{
		return accumulate(_units.begin(), _units.end(), 0,
			[](int sum, const auto& unit) { return sum + unit.health; });
	}

	vector<Unit*> Combat::find_targets(int idx)
	{
		vector<Unit*> targets;
		for (int i = 0; i < (int)_units.size(); i++)
			if (_units[i].type != _units[idx].type)
				targets.push_back(&_units[i]);

		return targets;
	}

	int Combat::iabs(int x) const
	{
		return x < 0 ? -x : x;
	}

	bool Combat::adjacent(const Point& p1, const Point& p2) const
	{
		return iabs(p1.x - p2.x) + iabs(p1.y - p2.y) == 1;
	}

	int Combat::any_adjacent(vector<Unit*> targets, int idx) const
	{
		for (int i = 0; i < (int)targets.size(); i++)
			if (adjacent(targets[i]->p, _units[idx].p))
				return true;

		return false;
	}

	vector<Unit*> Combat::find_adjacent(vector<Unit*> targets, int idx) const
	{
		vector<Unit*> result;
		for (int i = 0; i < (int)targets.size(); i++)
			if (adjacent(targets[i]->p, _units[idx].p))
				result.push_back(targets[i]);

		return result;
	}

	bool Combat::can_move(const Point& p) const
	{
		if (_area[p.y][p.x] == '#')
			return false;

		for (const auto& u : _units)
			if (u.p.x == p.x && u.p.y == p.y)
				return false;

		return true;
	}

	set<Point> Combat::targets_in_range(vector<Unit*> targets) const
	{
		set<Point> result;
		for (const auto& t: targets)
			for (int i = 0; i < 4; i++)
			{
				Point p(t->p.x + _move_x[i], t->p.y + _move_y[i]);
				if (can_move(p))
					result.insert(p);
			}

		return result;
	}

	map<Point, Point> Combat::find_sections(const Point& unit_point) const
	{
		queue<Point> queue;
		map<Point, Point> sections;
		queue.push(unit_point);
		sections[unit_point] = Point();
		while (queue.size() > 0)
		{
			Point p = queue.front();
			queue.pop();

			for (int i = 0; i < 4; i++)
			{
				Point np(p.x + _move_x[i], p.y + _move_y[i]);
				if (sections.find(np) != sections.end() || !can_move(np))
					continue;

				queue.push(np);
				sections[np] = p;
			}
		}

		return sections;
	}

	Path Combat::find_path(const Point& up, const set<Point>& in_range, map<Point, Point>& sections) const
	{
		Path path;
		for (const auto& ir : in_range)
		{
			if (sections.find(ir) == sections.end())
				continue;

			Point p = ir;
			Point next_step;
			int total_steps = 0;
			while (p != up)
			{
				total_steps++;
				next_step = p;
				p = sections[p];
			}

			Path new_path = Path(ir, next_step, total_steps);
			if (path.empty())
				path = new_path;
			else
				if (new_path < path)
					path = new_path;
		}

		return path;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Combat(input).run();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		for (int power = 4; ; power++)
		{
			int result = Combat(input, power).run(true);
			if (result != -1)
				return result;
		}

		return -1;
	}
}
