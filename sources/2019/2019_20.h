#ifndef __2019_20__
#define __2019_20__

#include "../shared/Solution.h"

namespace Day20_2019
{
	class Position
	{
	public:
		Position(int row = 0, int col = 0);
		bool operator < (const Position& other) const;
		bool operator == (const Position& other) const;
		bool operator != (const Position& other) const;

		int row, col;

		static const vector<Position> update;
	};

	// teleport target
	class Target
	{
	public:
		Target();
		Target(const string& id, bool inner);

		string id;
		Position position;
		bool inner;
	};

	// map of teleports: starting position to target id, position, inner flag
	typedef map<Position, Target> t_teleports;

	// the labyrinth
	typedef vector<string> t_labyrinth;

	// single route in labyrinth on one level
	class Route
	{
	public:
		Route(int length, const Position& target, int level_change);

		int length;
		Position target;
		int level_change;	  // teleport at position 'target' changes level +1 or -1
	};

	// vector of routes
	typedef vector<Route> t_routes;

	// map of routes from source teleport to target teleport (with length and level_change info)
	typedef map<Position, t_routes> t_paths;

	class Labyrinth
	{
	public:
		Labyrinth(const vector<string>& input);

		int walk_through_levels(bool recursive_spaces);

	private:
		t_labyrinth _labyrinth;
		t_teleports _teleports;
		Position _start;
		Position _finish;

		void add_teleport(int empty_row, int empty_col, int wall_row, int wall_col, int teleport_row, int teleport_col, const string& id, bool inner);
		
		t_routes bfs_find_routes(const Position& source);
		void recursive_find(const t_paths& paths, Position position, int teleports_used, int max_teleports, int level, int level_coeff, int steps, int& min_steps);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
