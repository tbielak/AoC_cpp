#ifndef __2016_10__
#define __2016_10__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
