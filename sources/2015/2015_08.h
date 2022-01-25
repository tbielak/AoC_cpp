#ifndef __2015_08__
#define __2015_08__

#include "../shared/Solution.h"

namespace Day08_2015
{
	class Main : public AoC::Solution
	{
	public:
		Main();

		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		int _bytes;

		static int count_chars(const string& s);
		static int encoded_length(const string& s);
	};
}

#endif
