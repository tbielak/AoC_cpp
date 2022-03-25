#ifndef __2017_15__
#define __2017_15__

#include "../shared/Solution.h"

namespace Day15_2017
{
    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output part_one(const vector<string>& input);
        virtual AoC::Output part_two(const vector<string>& input);

    private:
        static int solve(const vector<string>& input, int loops, int mod_a, int mod_b);
    };
}

#endif
