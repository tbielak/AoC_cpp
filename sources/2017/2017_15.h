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
        static pair<int64_t, int64_t> load(const vector<string>& input);
    };
}

#endif
