#include "2020_15.h"

namespace Day15_2020
{
	AoC::Output Main::both_parts(const string& input)
	{
		t_vecint ints;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			ints.push_back(stoi(s));

		const int target1 = 2020;
		const int target2 = 30000000;

		t_vecint result(2);
		t_vecint p(target2);
		t_vecint q(target2);
		for (int i = 0; i < (int)ints.size(); i++)
			p[ints[i]] = i + 1;

		int n = ints.back();
		for (int i = (int)ints.size() + 1; i <= target2; i++)
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
}
