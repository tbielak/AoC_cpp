#include "2015_10.h"

namespace Day10_2015
{
	AoC::Output Main::both_parts(const string& input)
	{
		int p1 = 0;
		int p2 = 0;
		string current = input;

		for (int j = 1; j <= 50; j++)
		{
			string next;
			int cnt = 0;
			char ch = 0;
			for (auto c : current)
			{
				if (c != ch)
				{
					if (ch)
						next += to_string(cnt) + ch;

					ch = c;
					cnt = 1;
				}
				else
					cnt++;
			}

			if (ch)
				next += to_string(cnt) + ch;

			current = next;
			if (j == 40) p1 = (int)current.size();
			if (j == 50) p2 = (int)current.size();
		}

		return make_pair(p1, p2);
	}
}
