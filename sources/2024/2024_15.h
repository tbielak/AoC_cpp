#ifndef __2024_15__
#define __2024_15__

#include "../shared/Solution.h"

namespace Day15_2024
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		Point& operator += (const Point& rhs);
		Point& operator -= (const Point& rhs);
		bool operator != (const Point& rhs) const;
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	class Warehouse
	{
	public:
		Warehouse(const vector<string>& input, bool expand = false);
		
		Warehouse& part_one();
		Warehouse& part_two();
		int count(char c) const;

	private:
		int _width, _height;
		vector<string> _map;
		Point _robot;
		string _moves;

		void move(const Point& d);
		void move_y(int dy);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
