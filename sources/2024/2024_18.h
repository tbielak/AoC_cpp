#ifndef __2024_18__
#define __2024_18__

#include "../shared/Solution.h"

namespace Day18_2024
{
	class Position
	{
	public:
		Position(int x, int y);
		Position(const string& s);
		
		bool operator < (const Position& rhs) const;
		bool operator == (const Position& rhs) const;
		string to_string() const;

		int x, y;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Position> load(const vector<string>& input);
		static int steps(size_t count, const vector<Position>& input, const Position& start, const Position& end);
	};
}

#endif
