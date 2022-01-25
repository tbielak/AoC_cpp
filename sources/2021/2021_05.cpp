#include "2021_05.h"

namespace Day05_2021
{
	Diagram::Diagram(const vector<string>& input)
	:	_width(0), _height(0)
	{
		// load input
		smatch matches;
		regex regex("([0-9]*),([0-9]*) -> ([0-9]*),([0-9]*)");

		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			_lines.push_back(make_pair(
				Point{ stoi(matches[1].str()), stoi(matches[2].str()) },
				Point{ stoi(matches[3].str()), stoi(matches[4].str()) }
			));
		}

		// find diagram width and height
		for (const auto& line : _lines)
		{
			const auto& [p1, p2] = line;
			_width = max(_width, p1.x);
			_width = max(_width, p2.x);
			_height = max(_height, p1.y);
			_height = max(_height, p2.y);
		}

		_width++;
		_height++;
	}

	int Diagram::count_overlaps(bool with_diagonals) const
	{
		// create diagram
		t_diagram diagram = t_diagram(_height, t_row());
		for (auto& row : diagram)
			row = t_row(_width, 0);

		// draw lines
		for (const auto& line : _lines)
		{
			const auto& [p1, p2] = line;
			if (p1.y == p2.y)
				draw_hrzontal_line(diagram, p1, p2);
			else
			if (p1.x == p2.x)
				draw_vertical_line(diagram, p1, p2);
			else
			if (with_diagonals)
				draw_diagonal_line(diagram, p1, p2);
		}

		// count overlaps
		int overlaps = 0;
		for (const auto& row : diagram)
			for (auto v : row)
				if (v > 1)
					overlaps++;

		return overlaps;
	}

	void Diagram::draw_hrzontal_line(t_diagram& tab, Point p1, Point p2) const
	{
		if (p1.x > p2.x)
			swap(p1, p2);

		for (int x = p1.x; x <= p2.x; x++)
			tab[p1.y][x]++;
	}

	void Diagram::draw_vertical_line(t_diagram& tab, Point p1, Point p2) const
	{
		if (p1.y > p2.y)
			swap(p1, p2);

		for (int y = p1.y; y <= p2.y; y++)
			tab[y][p1.x]++;
	}

	void Diagram::draw_diagonal_line(t_diagram& tab, Point p1, Point p2) const
	{
		if (p1.y > p2.y)
			swap(p1, p2);

		int steps = p2.y - p1.y;
		int coeff = (p1.x > p2.x) ? -1 : 1;
		for (int i = 0; i <= steps; i++)
			tab[p1.y + i][p1.x + coeff * i]++;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Diagram(input).count_overlaps(false);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Diagram(input).count_overlaps(true);
	}
}
