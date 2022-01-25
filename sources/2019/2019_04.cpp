#include "2019_04.h"

namespace Day04_2019
{
	AoC::Output Main::both_parts(const string& input)
	{
		size_t position = input.find_first_of('-');
		int from = stoi(input.substr(0, position));
		int to = stoi(input.substr(position + 1));

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
}
