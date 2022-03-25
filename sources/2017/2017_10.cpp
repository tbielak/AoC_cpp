#include "2017_10.h"
#include "KnotHash.h"

namespace Day10_2017
{
	AoC::Output Main::part_one(const string& input)
	{
		return KnotHash().mult(input);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return KnotHash().hash(input);
	}
}
