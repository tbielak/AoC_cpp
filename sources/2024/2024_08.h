#ifndef __2024_08__
#define __2024_08__

#include "../shared/Solution.h"

namespace Day08_2024
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	class Antennas
	{
	public:
		Antennas(const vector<string>& input);

		size_t part_one();
		size_t part_two();

	private:
		int _width, _height;

		typedef vector<Point> t_vecPoints;
		map<char, t_vecPoints> _map;
		set<Point> _output;

		bool add(int x, int y);
		void add(int x, int y, int dx, int dy);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
