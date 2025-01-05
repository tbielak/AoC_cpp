#include "2018_21.h"

// explained here:
// https://github.com/tbielak/AoC_cpp/blob/master/doc/2018_21.md

namespace Day21_2018
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		int arg = stoi(input[8].substr(5));

		int p1 = -1;
		int p2 = -1;
		set<int> values;

		int R3 = 0;
		while (1)
		{
			int R5 = R3 | 0x10000;
			R3 = arg;
			while (1)
			{
				R3 += R5 & 0xFF;
				R3 = ((R3 & 0xFFFFFF) * 0x1016B) & 0xFFFFFF;
				if (R5 < 0x100)
					break;

				int R2 = 0;
				while ((R2 + 1) * 0x100 <= R5)
					R2++;

				R5 = R2;
			}
		
			if (p1 == -1)
				p1 = R3;

			if (values.find(R3) != values.end())
				return make_pair(p1, p2);

			p2 = R3;
			values.insert(R3);
		}
	}
}
