#ifndef __2016_16__
#define __2016_16__

#include "../shared/Solution.h"

namespace Day16_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static string checksum(const string& input, int target_size);
	};
}

#endif
