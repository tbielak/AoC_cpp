#ifndef __2024_11__
#define __2024_11__

#include "../shared/Solution.h"

namespace Day11_2024
{
	class StoneCounter
	{
	public:
		StoneCounter(const string& input);
		const StoneCounter& blink(int steps);
		int64_t count() const;

	private:
		typedef map<int64_t, int64_t> t_data;
		t_data _data;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
