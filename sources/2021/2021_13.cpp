#include "2021_13.h"

namespace Day13_2021
{
	char Main::fold(char a, char b)
	{
		return (a == dot || b == dot) ? dot : empty;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// load points
		t_points points;
		size_t idx = 0;
		for (; idx < input.size(); idx++)
		{
			const string& s = input[idx];
			if (s == "")
				break;

			size_t pos = s.find_first_of(',');
			points.push_back(make_pair(stoi(s.substr(0, pos)), stoi(s.substr(pos + 1))));
		}

		// load folds
		t_folds folds;
		idx++;
		for (; idx < input.size(); idx++)
		{
			const string& s = input[idx];
			size_t pos = s.find_first_of('=');
			folds.push_back(make_pair(s[pos - 1], stoi(s.substr(pos + 1))));
		}

		// size of a paper
		int width = 0;
		int height = 0;
		for (const auto& p : points)
		{
			width = max(width, p.first);
			height = max(height, p.second);
		}
		width++;
		height++;

		// paper with dots
		vector<string> paper = vector<string>(height, string(width, empty));
		for (const auto& p : points)
			paper[p.second][p.first] = dot;

		// folding
		bool first_fold = true;
		vector<string> result;
		for (const auto& f : folds)
		{
			if (f.first == 'y')
			{
				// fold along y
				int dy = f.second - 1;
				for (int y = f.second + 1; y < height; y++, dy--)
					for (int x = 0; x < width; x++)
						paper[dy][x] = fold(paper[dy][x], paper[y][x]);

				height = f.second;
			}
			else
			{
				// fold along x
				int dx = f.second - 1;
				for (int x = f.second + 1; x < width; x++, dx--)
					for (int y = 0; y < height; y++)
						paper[y][dx] = fold(paper[y][dx], paper[y][x]);

				width = f.second;
			}

			if (first_fold)
			{
				// count dots on first fold
				int count = 0;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width; x++)
						if (paper[y][x] == dot)
							count++;

				result.push_back(to_string(count));
				first_fold = false;
			}
		}

		// show paper
		for (int y = 0; y < height; y++)
			result.push_back(paper[y].substr(0, width));

		return result;
	}
}
