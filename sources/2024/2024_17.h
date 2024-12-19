#ifndef __2024_17__
#define __2024_17__

#include "../shared/Solution.h"

namespace Day17_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<vector<int64_t>, string> load(const vector<string>& input);
		static int64_t combo(const vector<int64_t>& regs, int op);
		static string execute(vector<int64_t>& regs, string program);
	};
}

#endif
