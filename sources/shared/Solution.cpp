#include "Solution.h"

namespace AoC
{
    Output Solution::part_one(const string& input)
    {
        (void)(input);
        return Output();
    }

    Output Solution::part_one(const vector<string>& input)
    {
        (void)(input);
        return Output();
    }

    Output Solution::part_two(const string& input)
    {
        (void)(input);
        return Output();
    }

    Output Solution::part_two(const vector<string>& input)
    {
        (void)(input);
        return Output();
    }

    Output Solution::both_parts(const string& input)
    {
        (void)(input);
        return Output();
    }

    Output Solution::both_parts(const vector<string>& input)
    {
        (void)(input);
        return Output();
    }

    t_output Solution::run(const vector<string>& input)
    {
        Output output;
        t_exectimes exec_times;
        auto t0 = chrono::steady_clock::now();
        output = (input.size() > 1) ? both_parts(input) : both_parts(input[0]);
        auto t1 = chrono::steady_clock::now();
        if (!output.empty())
        {
            exec_times.push_back(chrono::duration<double>((t1 - t0) * 1000).count());
            return make_pair(output, exec_times);
        }

        t0 = chrono::steady_clock::now();
        output = (input.size() > 1) ? part_one(input) : part_one(input[0]);
        t1 = chrono::steady_clock::now();
        exec_times.push_back(chrono::duration<double>((t1 - t0) * 1000).count());

        t0 = chrono::steady_clock::now();
        Output p2 = (input.size() > 1) ? part_two(input) : part_two(input[0]);
        t1 = chrono::steady_clock::now();
        if (!p2.empty())
        {
            output._lines.insert(output._lines.end(), p2._lines.begin(), p2._lines.end());
            exec_times.push_back(chrono::duration<double>((t1 - t0) * 1000).count());
        }

        return make_pair(output, exec_times);
    }
}
