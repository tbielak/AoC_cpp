#ifndef __2016_09__
#define __2016_09__

#include "../shared/Solution.h"

namespace Day09_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static intmax_t decompressed_length(const string& input, size_t begin_index, size_t end_index, bool recursive);
	};
}

#endif
