#ifndef __2021_13__
#define __2021_13__

#include "../shared/Solution.h"

namespace Day13_2021
{
	typedef vector<pair<int, int>> t_points;
	typedef vector<pair<char, int>> t_folds;

	const char dot = -37;		// use -37 instead of '#'
	const char empty = ' ';		// use ' ' instead of '.'

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static char fold(char a, char b);
	};
}

#endif
