#ifndef __2023_01__
#define __2023_01__

#include "../shared/Solution.h"

namespace Day01_2023
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<string> _empty, _fdigits, _rdigits;
		static int digit(const string& s, const vector<string>& words);
		static int sum(const vector<string>& input, const vector<string>& fwd, const vector<string>& rev);
	};
}

#endif
