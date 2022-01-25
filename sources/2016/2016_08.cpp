#include "2016_08.h"

namespace Day08_2016
{
	t_commands Main::load(const vector<string>& input)
	{
		t_commands cmds;
		smatch matches;
		regex regex_rect("rect ([0-9]*)x([0-9]*)");
		regex regex_rotate("rotate (row y|column x)=([0-9]*) by ([0-9]*)");

		for (const auto& line : input)
		{
			if (line[1] == 'e')
			{
				regex_search(line, matches, regex_rect);
				cmds.push_back({ 'f', stoi(matches[1]), stoi(matches[2]) });
			}
			else
			{
				regex_search(line, matches, regex_rotate);
				cmds.push_back({ matches[1] == "row y" ? 'r' : 'c', stoi(matches[2]), stoi(matches[3]) });
			}
		}

		return cmds;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		t_commands cmds = load(input);

		vector<string> screen(6, string(50, ' '));
		for (const auto& c : cmds)
		{
			switch (c.id)
			{
				case 'r':
				{
					string row = screen[c.p1];
					int j = c.p2;
					for (int i = 0; i < 50; i++)
					{
						screen[c.p1][j++] = row[i];
						j %= 50;
					}

					break;
				}

				case 'c':
				{
					string col;
					for (int i = 0; i < 6; i++)
						col += screen[i][c.p1];

					int j = c.p2;
					for (int i = 0; i < 6; i++)
					{
						screen[j++][c.p1] = col[i];
						j %= 6;
					}

					break;
				}

				default: // 'f'
				{
					for (int y = 0; y < c.p2; y++)
						for (int x = 0; x < c.p1; x++)
							screen[y][x] = -37;

					break;
				}
			}
		}

		int count = 0;
		for (int y = 0; y < 6; y++)
			for (int x = 0; x < 50; x++)
				if (screen[y][x] == -37)
					count++;

		vector<string> result;
		result.push_back(to_string(count));
		result.insert(result.end(), screen.begin(), screen.end());
		return result;
	}
}
