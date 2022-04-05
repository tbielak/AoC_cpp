#ifndef __2017_16__
#define __2017_16__

#include "../shared/Solution.h"

namespace Day16_2017
{
	class DanceMove
	{
	public:
		DanceMove(char cmd, int p1, int p2 = 0);

		function<void(string&)> dance_move;
	};

	typedef vector<DanceMove> t_dance;

    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output part_one(const string& input);
        virtual AoC::Output part_two(const string& input);

	private:
		static t_dance load(const string& input);
		static void do_the_dance(string& progs, const t_dance& dance);
    };
}

#endif
