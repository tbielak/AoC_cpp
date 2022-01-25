#include "2015_25.h"

namespace Day25_2015
{
	AoC::Output Main::part_one(const string& input)
	{
		smatch matches;
		regex regex("(.*) row ([0-9]*), column ([0-9]*).");
		regex_search(input, matches, regex);
		int req_row = stoi(matches[2].str());
		int req_column = stoi(matches[3].str());

		int row = 1;
		int col = 1;
		int max_row = 1;
		int64_t code = 20151125;
		while (1)
		{
			code = (code * 252533) % 33554393;
			if (row == 1)
			{
				max_row++;
				row = max_row;
				col = 1;
			}
			else
			{
				row--;
				col++;
			}

			if (row == req_row && col == req_column)
				return code;
		}

		return 0;
	}
}
