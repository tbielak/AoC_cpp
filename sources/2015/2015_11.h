#ifndef __2015_11__
#define __2015_11__

#include "../shared/Solution.h"

namespace Day11_2015
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const string& input);

	private:
		static void inc(string& password);
		static bool valid(const string& password);
		static bool next(string& password);
	};
}

#endif
