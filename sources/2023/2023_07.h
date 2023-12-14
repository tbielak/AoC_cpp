#ifndef __2023_07__
#define __2023_07__

#include "../shared/Solution.h"

namespace Day07_2023
{
	class Hand
	{
	public:
		Hand(const string& order, const string& input, int joker_index);

		bool operator < (const Hand& rhs) const;

		int type;
		string ordering;
		int bid;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int solve(const string& order, const vector<string>& input, int joker_index);
	};
}

#endif
