#ifndef __2024_21__
#define __2024_21__

#include "../shared/Solution.h"

namespace Day21_2024
{
	class Position
	{
	public:
		Position(int row = 0, int col = 0);
		
		bool operator < (const Position& rhs) const;
		bool operator == (const Position& rhs) const;
		
		int row, col;
	};

	class Solver
	{
	public:
		Solver();
		int64_t go(const vector<string>& input, int target_depth);

	private:
		int _target_depth;
		set<Position> _valid_numeric_positions, _valid_directional_positions;
		map<char, Position> _numeric_keypad, _directional_keypad;
		map<string, int64_t> _cache;

		map<char, Position> create_keypad(const vector<string>& layout, set<Position>& valid);
		vector<string> generate_reversed(const Position& start, const Position& end, const set<Position>& valid);
		vector<string> generate(const Position& start, const Position& end, const set<Position>& valid);
		int64_t go(char start, char end, int depth);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
