#include "2016_16.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

namespace Day16_2016
{
	string checksum(const string& input, int target_size)
	{
		// create pattern
		string data = input;
		while ((int)data.size() < target_size)
		{
			data += '0';
			for (int i = (int)data.size() - 2; i >= 0; i--)
				data += data[i] ^ 1;
		}

		// calculate checksum
		while ((target_size & 1) == 0)
		{
			target_size /= 2;
			for (int i = 0; i < target_size; i++)
				data[i] = char(((data[i * 2] ^ data[i * 2 + 1]) ^ 1) + '0');
		}

		return data.substr(0, target_size);
	}

	string part_one(const t_input& input)
	{
		return checksum(input[0], 272);
	}

	string part_two(const t_input& input)
	{
		return checksum(input[0], 35651584);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(p1);
		solutions.push_back(p2);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
