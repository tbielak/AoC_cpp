#ifndef __2016_10__
#define __2016_10__

#include "../shared/Solution.h"

namespace Day10_2016
{
	class LowHigh
	{
	public:
		LowHigh(int low, int high);

		int low;
		int high;
	};

	typedef map<int, LowHigh> t_bots;
	typedef map<int, int> t_outputbin;

	class SetIns
	{
	public:
		SetIns(int bot, int value);

		int bot;
		int value;
	};

	typedef vector<SetIns> t_setins;

	class Target
	{
	public:
		Target(char target, int index);

		char target;
		int index;
	};

	class MoveIns
	{
	public:
		MoveIns(const string& low_target, int low_index, const string& high_target, int high_index);

		Target low;
		Target high;
	};

	typedef map<int, MoveIns> t_moveins;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static void set_value(t_bots& bots, const SetIns& ins, const LowHigh& cmp, int& cmp_bot);
	};
}

#endif
