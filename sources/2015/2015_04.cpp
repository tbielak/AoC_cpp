#include "2015_04.h"

// below: including single-MD5-transform routine shared by two CPU solutions and one GPU solution
// note: CPU version requires an empty prefix
#define MD5_SINGLE_TRANSFORM_PREFIX
#define MD5_SINGLE_TRANSFORM_FNAME Day_04_2015_CPU_md5_single_transform
#include "../MD5/MD5_single_transform.h"

namespace Day04_2015
{
	int Main::solve(int part, const string& line)
	{
		int i = 1;
		const vector<unsigned int> result_mask = { 0xff0f0000, 0xff000000 };

		while (1)
		{
			// prepare input
			string input = line + to_string(i);

			// copy input to 64-byte buffer, required for single MD5 transform
			vector<unsigned char> buffer(64, 0);
			copy(input.begin(), input.end(), buffer.begin());

			// place 0x80 at the end of the string to create correct MD5 padding
			buffer[input.size()] = 0x80;

			// place length (in bits) of the string at 56th buffer element, as required by MD5 padding
			buffer[56] = (unsigned char)(input.size() * 8);

			// do one MD5 transform and get part of MD5 hash
			unsigned int result = MD5_SINGLE_TRANSFORM_FNAME((unsigned int*)(&buffer[0]));

			// check requested number of zeros
			if ((result & result_mask[part - 1]) == result)
				return i;

			i++;
		}

		return -1;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return solve(1, input);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return solve(2, input);
	}
}

// undefine macros (different definitions for CPU/GPU version)
#undef MD5_SINGLE_TRANSFORM_PREFIX
#undef MD5_SINGLE_TRANSFORM_FNAME
