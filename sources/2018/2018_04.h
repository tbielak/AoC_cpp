#ifndef __2018_04__
#define __2018_04__

#include "../shared/Solution.h"

namespace Day04_2018
{
	class OneHour
	{
	public:
		OneHour();
		
		void short_nap(int falls_asleep, int wakes_up);
		int minutes_asleep() const;
		pair<int, int> max_minute() const;

	private:
		vector<int> _minutes;
	};

	typedef map<int, OneHour> t_guards;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	
	private:
		static t_guards load(vector<string> input);
	};
}

#endif
