#ifndef __2017_10__
#define __2017_10__

#include "../shared/Solution.h"

namespace Day10_2017
{
    typedef vector<int> t_data;

    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output part_one(const string& input);
        virtual AoC::Output part_two(const string& input);

    private:
        static void Knot_Hash_single_round(t_data& data, const t_data& lengths, int& pos, int& skip_size);
        static char hex(int v);
    };
}

#endif
