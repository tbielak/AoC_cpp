#include "2015_17.h"

namespace Day17_2015
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		t_vecint ints;
		for (const auto& line : input)
			ints.push_back(stoi(line));

		t_vecint result(2);

		int minc = (int)ints.size();
		for (int part = 1; part <= 2; part++)
		{
			int cnt = 0;
			int loop = 1 << ints.size();
			for (int j = 0; j < loop; j++)
			{
				int m = 0;
				int v = 0;
				int b = j;
				for (size_t i = 0; i < ints.size(); i++)
				{
					if (b & 1)
					{
						m++;
						v += ints[i];
					}

					b >>= 1;
				}

				if (v == 150)
				{
					if (part == 1)
					{
						cnt++;
						minc = min(minc, m);
					}
					else
					{
						if (m == minc)
							cnt++;
					}
				}
			}

			result[part - 1] = cnt;
		}

		return result;
	}
}
