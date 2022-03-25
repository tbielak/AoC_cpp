#ifndef __2017_14__
#define __2017_14__

#include "../shared/Solution.h"

namespace Day14_2017
{
    typedef vector<bool> t_row;
    typedef vector<t_row> t_matrix;

    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output part_one(const string& input);
        virtual AoC::Output part_two(const string& input);

    private:
        static pair<int, int> find(const t_matrix& used);
        static void recursive_free(t_matrix& used, pair<int, int> pos);
    };
}

#endif
