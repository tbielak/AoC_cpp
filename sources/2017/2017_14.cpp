#include "2017_14.h"
#include "KnotHash.h"

namespace Day14_2017
{
	AoC::Output Main::part_one(const string& input)
	{
		static vector<int> bit_count = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

		int used = 0;
		for (int i = 0; i < 128; i++)
		{
			string h = KnotHash().hash(input + "-" + to_string(i));
			for (int j = 0; j < 32; j++)
				used += bit_count[(h[j] < 'a') ? h[j] - '0' : h[j] - 'a' + 10];
		}

		return used;
	}

	pair<int, int> Main::find(const t_matrix& used)
	{
		for (int i = 0; i < (int)used.size(); i++)
			for (int j = 0; j < (int)used[i].size(); j++)
				if (used[i][j])
					return make_pair(i, j);

		return make_pair(-1, -1);
	}

	void Main::recursive_free(t_matrix& used, pair<int, int> pos)
	{
		auto [i, j] = pos;
		used[i][j] = false;
		
		if (i > 0 && used[i - 1][j])
			recursive_free(used, make_pair(i - 1, j));
		
		if (i < (int)used.size() - 1 && used[i + 1][j])
			recursive_free(used, make_pair(i + 1, j));

		if (j > 0 && used[i][j - 1])
			recursive_free(used, make_pair(i, j - 1));

		if (j < (int)used[i].size() - 1 && used[i][j + 1])
			recursive_free(used, make_pair(i, j + 1));
	}

	AoC::Output Main::part_two(const string& input)
	{
		t_matrix used = t_matrix(128, t_row(128, false));

		for (int i = 0; i < 128; i++)
		{
			string h = KnotHash().hash(input + "-" + to_string(i));
			for (int j = 0; j < 32; j++)
			{
				int v = (h[j] < 'a') ? h[j] - '0' : h[j] - 'a' + 10;
				for (int k = 0; k < 4; k++)
				{
					if ((v & 8) > 0)
						used[i][j * 4 + k] = true;

					v <<= 1;
				}
			}
		}

		int count = 0;
		while (1)
		{
			auto pos = find(used);
			if (pos.first == -1)
				break;

			count++;
			recursive_free(used, pos);
		}

		return count;
	}
}
