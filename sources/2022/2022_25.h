#ifndef __2022_25__
#define __2022_25__

#include "../shared/Solution.h"

namespace Day25_2022
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);

	private:
		static int64_t SNAFU_to_dec(const string& s);
		static string dec_to_SNAFU(int64_t v);
	};
}

#endif
