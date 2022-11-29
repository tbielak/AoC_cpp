#ifndef __2019_18__
#define __2019_18__

#include "../shared/Solution.h"

namespace Day18_2019
{
	typedef vector<string> t_labyrinth;

	class Position
	{
	public:
		Position(int row = 0, int col = 0);
		bool operator < (const Position& other) const;

		int row, col;
	};

	typedef vector<Position> t_positions;
	typedef vector<vector<int>> t_distance;
	
	class KeyRing   // funny class name ;)
	{
	public:
		KeyRing(int count = 0);
		bool operator < (const KeyRing& other) const;

		void add(int i);
		void drop(int i);
		bool available(int i) const;
		bool all() const;

	private:
		int _bitset;
		int _all;
	};

	class Cache
	{
	public:
		bool update(const KeyRing& keys, const t_positions& positions, int steps);

	private:
		typedef pair<KeyRing, t_positions> t_cacheKey;
		map<t_cacheKey, int> _map;
	};

	class Solver
	{
	public:
		Solver(const t_labyrinth& lab);
		void four_robots();

		int execute();

	private:
		int _shortest;
		t_labyrinth _lab;
		t_positions _start;
		KeyRing _keys;
		Cache _cache;

		const t_positions _directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		const t_labyrinth _lab_update = { ".#.", "###", ".#." };

		void recursive_search(t_positions& positions, int steps);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
