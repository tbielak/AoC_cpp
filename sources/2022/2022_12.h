#ifndef __2022_12__
#define __2022_12__

#include "../shared/Solution.h"

namespace Day12_2022
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		bool operator == (const Point& rhs) const;
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	typedef pair<Point, int> t_state;
	typedef queue<t_state> t_queue;
	typedef set<Point> t_visited;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool climbing(char from, char to);
		static int bfs(const vector<string>& input, const Point& start);
	};
}

#endif
