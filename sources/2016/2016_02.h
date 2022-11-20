#ifndef __2016_02__
#define __2016_02__

#include "../shared/Solution.h"

namespace Day02_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static char press(const vector<string>& key_map, const string& digit);
		static string enter_code(const vector<string>& key_map, const vector<string>& input);
	};
}

#endif
