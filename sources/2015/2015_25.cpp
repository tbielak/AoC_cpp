#include "2015_25.h"

namespace Day25_2015
{
	uintmax_t part_one(int req_row, int req_column)
	{
		int row = 1;
		int col = 1;
		int max_row = 1;
		uintmax_t code = 20151125;
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

	t_output main(const t_input& input)
	{
		smatch matches;
		regex regex("(.*) row ([0-9]*), column ([0-9]*).");
		regex_search(input[0], matches, regex);
		int row = stoi(matches[2].str());
		int column = stoi(matches[3].str());
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(row, column);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
