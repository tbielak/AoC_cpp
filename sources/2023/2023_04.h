#ifndef __2023_04__
#define __2023_04__

#include "../shared/Solution.h"

namespace Day04_2023
{
	using Numbers = set<int>;
	using Cards = map<int, int>;
	
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static Numbers load(const string& s);
		static Cards load(const vector<string>& input);
	};
}

#endif
