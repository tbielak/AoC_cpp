#ifndef __2020_08__
#define __2020_08__

#include "../shared/Solution.h"

namespace Day08_2020
{
	typedef pair<char, int> t_instruction;
	typedef vector<t_instruction> t_code;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_code load(const vector<string>& input);
		static bool run(const t_code& code, int& acc);
		static pair<bool, int> fix_and_run(t_code& code, char from, char to);
	};
}

#endif
