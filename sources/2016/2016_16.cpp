#include "2016_16.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

namespace Day16_2016
{
	string Main::checksum(const string& input, int target_size)
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

	AoC::Output Main::part_one(const string& input)
	{
		return checksum(input, 272);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return checksum(input, 35651584);
	}
}
