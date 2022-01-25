#include "2020_06.h"

namespace Day06_2020
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		vector<string> sinput = input;
		sinput.push_back("");
		sinput.push_back("");

		vector<size_t> result(2);
		for (size_t part = 1; part <= 2; part++)
		{
			int group = 0;
			size_t sum = 0;
			bool next_group = false;

			size_t char_count = 'z' - 'a' + 1;
			vector<int> x(char_count, 0);
			for (const auto& s : sinput)
			{
				if (next_group)
				{
					if (part == 1)
						sum += count_if(x.begin(), x.end(), [](auto v) { return v > 0; });
					else
						sum += count(x.begin(), x.end(), group);

					x = vector<int>(char_count, 0);
					next_group = false;
					group = 0;
				}

				if (s == "")
					next_group = true;
				else
				{
					group++;
					for (auto c : s)
						x[c - 'a']++;
				}
			}

			result[part - 1] = sum;
		}

		return result;
	}
}
