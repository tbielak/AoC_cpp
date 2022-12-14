#ifndef __2018_15__
#define __2018_15__

#include "../shared/Solution.h"

namespace Day15_2018
{
	class Point
	{
	public:
		Point(int x = -1, int y = -1);

		bool operator < (const Point& rhs) const;
		bool operator != (const Point& rhs) const;

		int x, y;
	};

	class Path
	{
	public:
		Path();
		Path(const Point& target, const Point& next_step, int total_steps);

		bool operator < (const Path& rhs) const;
		bool empty() const;

		Point target;
		Point next_step;
		int total_steps;
	};

	class Unit
	{
	public:
		Unit(const Point& p, char type, int power);

		Point p;
		char type;	// 'G' or 'E'
		int health;
		int power;
	};

	class Combat
	{
	public:
		Combat(const vector<string>& input, int elf_power = 3);

		int run(bool fail_if_elf_dead = false);

	private:
		static vector<int> _move_x;
		static vector<int> _move_y;
		const vector<string>& _area;
		vector<Unit> _units;

		static bool reading_order(const Unit& me, const Unit& other);
		static bool health_reading_order(const Unit* me, const Unit* other);
		int total_health() const;

		vector<Unit*> find_targets(int idx);

		int iabs(int x) const;
		bool adjacent(const Point& p1, const Point& p2) const;
		int any_adjacent(vector<Unit*> targets, int idx) const;
		vector<Unit*> find_adjacent(vector<Unit*> targets, int idx) const;

		bool can_move(const Point& p) const;
		set<Point> targets_in_range(vector<Unit*> targets) const;
		map<Point, Point> find_sections(const Point& unit_point) const;
		Path find_path(const Point& up, const set<Point>& in_range, map<Point, Point>& sections) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
