#include "2015_17.h"

namespace Day17_2015
{
	t_vecint both_parts(const t_vecint& input)
	{
		t_vecint result(2);

		int minc = (int)input.size();
		for (int part = 1; part <= 2; part++)
		{
			int cnt = 0;
			int loop = 1 << input.size();
			for (int j = 0; j < loop; j++)
			{
				int m = 0;
				int v = 0;
				int b = j;
				for (size_t i = 0; i < input.size(); i++)
				{
					if (b & 1)
					{
						m++;
						v += input[i];
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

	t_output main(const t_input& input)
	{
		t_vecint vinput;
		for (const auto& line : input)
			vinput.push_back(stoi(line));


		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(vinput);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px[0]));
		solutions.push_back(to_string(px[1]));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
