#include "2023_11.h"

namespace Day11_2023
{
	vector<size_t> Main::find_empty_cols(const vector<string>& input)
	{
		vector<bool> only_dots = vector<bool>(input[0].size(), true);
		for (size_t y = 0; y < input.size(); y++)
			for (size_t x = 0; x < input[y].size(); x++)
				if (input[y][x] != '.')
					only_dots[x] = false;

		vector<size_t> cols;
		for (size_t i = 0; i < only_dots.size(); i++)
			if (only_dots[i])
				cols.push_back(i);

		return cols;
	}
	
	vector<size_t> Main::find_empty_rows(const vector<string>& input)
	{
		vector<size_t> rows;
		for (size_t y = 0; y < input.size(); y++)
		{
			bool only_dots = true;
			for (size_t x = 0; x < input[y].size(); x++)
				if (input[y][x] != '.')
					only_dots = false;

			if (only_dots)
				rows.push_back(y);
		}

		return rows;
	}

	size_t Main::distance(const vector<size_t>& indices, size_t from, size_t to, size_t factor)
	{
		size_t v = to - from;
		for (size_t i : indices)
			if (i > from && i <= to)
				v += factor - 1;

		return v;
	}

	size_t Main::solve(const vector<string>& input, size_t expand_factor)
	{
		auto cols = find_empty_cols(input);
		auto rows = find_empty_rows(input);

		vector<Point> pts;
		for (size_t y = 0; y < input.size(); y++)
			for (size_t x = 0; x < input[y].size(); x++)
				if (input[y][x] == '#')
					pts.push_back({ y, x });

		size_t sum = 0;
		for (size_t i = 0; i < pts.size(); i++)
			for (size_t j = i + 1; j < pts.size(); j++)
			{
				size_t x1 = pts[i].x;
				size_t x2 = pts[j].x;
				size_t y1 = pts[i].y;
				size_t y2 = pts[j].y;
				if (x1 > x2)
					swap(x1, x2);
				if (y1 > y2)
					swap(y1, y2);

				sum += distance(cols, x1, x2, expand_factor);
				sum += distance(rows, y1, y2, expand_factor);
			}

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, 2);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 1000000);
	}
}
