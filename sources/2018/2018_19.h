#ifndef __2018_19__
#define __2018_19__

#include "../shared/Solution.h"

namespace Day19_2018
{
	typedef vector<int> t_instruction;
	typedef vector<int> t_registers;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void execute(t_registers& regs, const t_instruction& code);
		static t_instruction parse(const string& input);
		static pair<int, vector<t_instruction>> load(const vector<string>& input);

		static int execute(const vector<string>& input, int R0);
	};
}

#endif
