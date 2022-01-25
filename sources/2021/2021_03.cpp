#include "2021_03.h"

namespace Day03_2021
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		string gamma_bin = input[0];
		string epsilon_bin = input[0];
		for (int i = 0; i < (int)input[0].size(); i++)
		{
			int zeros = (int)count_if(input.begin(), input.end(), [i](const auto& s) { return s[i] == '0'; });
			int ones = (int)input.size() - zeros;
			gamma_bin[i] = char(zeros <= ones) + '0';
			epsilon_bin[i] = char(zeros > ones) + '0';
		}

		int gamma_rate = stoi(gamma_bin, nullptr, 2);
		int epsilon_rate = stoi(epsilon_bin, nullptr, 2);
		return gamma_rate * epsilon_rate;
	}

	int Main::find_rating(const vector<string>& x, int xor_mask)
	{
		vector<int> consider = vector<int>(x.size(), true);

		while (1)
		{
			for (int i = 0; i < (int)x[0].size(); i++)
			{
				int zeros = 0;
				int ones = 0;
				for (size_t j = 0; j < x.size(); j++)
				{
					if (consider[j])
					{
						if (x[j][i] == '1')
							ones++;
						else
							zeros++;
					}
				}

				char keep = char(((ones >= zeros) ^ xor_mask) + int('0'));
				for (size_t j = 0; j < x.size(); j++)
				{
					if (consider[j])
					{
						if (x[j][i] != keep)
							consider[j] = false;
					}
				}

				if (count_if(consider.begin(), consider.end(), [](const auto& c) { return c; }) == 1)
				{
					for (size_t j = 0; j < x.size(); j++)
						if (consider[j])
							return stoi(x[j], nullptr, 2);
				}
			}
		}
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int oxygen_rate = find_rating(input, 0);
		int co2_rate = find_rating(input, 1);
		return oxygen_rate * co2_rate;
	}
}
