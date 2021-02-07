#include "2020_15.h"

namespace Day15_2020
{
	t_vecint both_parts(const t_vecint& input)
	{
		const int target1 = 2020;
		const int target2 = 30000000;

		t_vecint result(2);
		t_vecint p(target2);
		t_vecint q(target2);
		for (int i = 0; i < (int)input.size(); i++)
			p[input[i]] = i + 1;

		int n = input.back();
		for (int i = (int)input.size() + 1; i <= target2; i++)
		{
			n = q[n] ? p[n] - q[n] : 0;
			q[n] = p[n];
			p[n] = i;

			if (i == target1)
				result[0] = n;
		}

		result[1] = n;
		return result;
	}

	t_output main(const t_input& input)
	{
		t_vecint vinput;
		string s;
		stringstream ss(input[0]);
		while (getline(ss, s, ','))
			vinput.push_back(stoi(s));

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(vinput);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px[0]));
		solutions.push_back(to_string(px[1]));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
