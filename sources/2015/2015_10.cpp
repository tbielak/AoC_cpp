#include "2015_10.h"

namespace Day10_2015
{
	pair<size_t, size_t> both_parts(string input)
	{
		size_t p1 = 0;
		size_t p2 = 0;
		for (int j = 1; j <= 50; j++)
		{
			string next;
			int cnt = 0;
			char ch = 0;
			for (size_t i = 0; i < input.size(); i++)
			{
				if (input[i] != ch)
				{
					if (ch)
						next += to_string(cnt) + ch;

					ch = input[i];
					cnt = 1;
				}
				else
					cnt++;
			}

			if (ch)
				next += to_string(cnt) + ch;

			input = next;
			if (j == 40) p1 = input.size();
			if (j == 50) p2 = input.size();
		}

		return make_pair(p1, p2);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
