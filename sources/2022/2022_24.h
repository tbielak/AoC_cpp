#ifndef __2022_24__
#define __2022_24__

#include "../shared/Solution.h"

namespace Day24_2022
{
	typedef vector<uint8_t> t_row;
	typedef vector<t_row> t_map;

	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;

		int x, y;
	};

	class State
	{
	public:
		State(const Point& p, const t_map& m, int steps = 0, uint8_t phase = 0);

		Point p;
		t_map m;
		int steps;
		uint8_t phase;
		// phase: 0 = start point and stop point not visited
		//        1 = start point visited once, stop point not visited
		//        2 = start point visited once, stop point visited once
		//        3 = start point visited twice, stop point visited once
		//        4 = start point visited twice, stop point visited twice
	};

	class Solver
	{
	public:
		Solver(const vector<string>& input);
		int execute(int target_phase);

	private:
		int _height, _width;
		Point _start, _end;
		queue<State> _q;
		map<size_t, t_map> _cache;
		set<pair<size_t, Point>> _visited;

		void do_move(t_map& dst, const t_map& src) const;
		t_map blizzard(const t_map& curr, int steps);
		bool valid(const Point& p, int steps, const t_map& next) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
