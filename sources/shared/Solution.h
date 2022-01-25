#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "Output.h"

namespace AoC
{
    typedef vector<double> t_exectimes;
    typedef pair<Output, t_exectimes> t_output;

    class Solution
    {
    public:
        virtual Output part_one(const string& input);
        virtual Output part_one(const vector<string>& input);

        virtual Output part_two(const string& input);
        virtual Output part_two(const vector<string>& input);

        virtual Output both_parts(const string& input);
        virtual Output both_parts(const vector<string>& input);

        t_output run(const vector<string>& input);
    };
}

#endif
