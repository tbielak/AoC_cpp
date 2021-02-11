#include "2019_04.h"

namespace Day04_2019
{
	vector<int> both_parts(int from, int to)
	{
		vector<int> result(2);
		for (int i = from; i <= to; i++)
		{
			// part one
			string password = to_string(i);
			bool decreasing = false;
			bool repeat = false;
			for (int j = 1; j < 6; j++)
			{
				if (password[j] < password[j - 1])
					decreasing = true;

				if (password[j] == password[j - 1])
					repeat = true;
			}

			if (!decreasing && repeat)
			{
				result[0]++;

				// part two
				bool valid = false;
				char prev = 0;
				int c = 0;
				for (int j = 0; j < 6; j++)
				{
					if (password[j] == prev)
						c++;
					else
					{
						if (c == 2)
							valid = true;

						c = 1;
						prev = password[j];
					}
				}

				if (c == 2 || valid)
					result[1]++;
			}
		}

		return result;
	}

	t_output main(const t_input& input)
	{
		size_t position = input[0].find_first_of('-');
		int from = stoi(input[0].substr(0, position));
		int to = stoi(input[0].substr(position + 1));

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(from, to);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px[0]));
		solutions.push_back(to_string(px[1]));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
