#ifndef __2021_05__
#define __2021_05__

#include "../shared/Solution.h"

namespace Day05_2021
{
	struct Point
	{
		int x, y;
	};

	typedef pair<Point, Point> t_line;
	typedef vector<t_line> t_lines;

	typedef vector<int> t_row;
	typedef vector<t_row> t_diagram;

	class Diagram
	{
	public:
		Diagram(const vector<string>& input);

		int count_overlaps(bool with_diagonals) const;

	private:
		t_lines _lines;
		int _width, _height;

		void draw_hrzontal_line(t_diagram& tab, Point p1, Point p2) const;
		void draw_vertical_line(t_diagram& tab, Point p1, Point p2) const;
		void draw_diagonal_line(t_diagram& tab, Point p1, Point p2) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
