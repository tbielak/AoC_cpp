#ifndef __2016_07__
#define __2016_07__

#include "../shared/Solution.h"

namespace Day07_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool supports_TLS(const string& s);
		static bool supports_SSL(const string& s);
	};
}

#endif
