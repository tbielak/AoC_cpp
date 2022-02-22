#ifndef __2017_08__
#define __2017_08__

#include "../shared/Solution.h"

namespace Day08_2017
{
    typedef map<string, int> t_regs;

    class Instruction
    {
    public:
        Instruction(const string& input);

        void execute(t_regs& regs, int& highest_value) const;

    private:
        string dst, cmp;
        int dst_value, cmp_value;
        function<bool(int, int)> comparator;
    };

    typedef vector<Instruction> t_vecIns;

    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output both_parts(const vector<string>& input);

    private:
        static t_vecIns load(const vector<string>& input);
        static pair<t_regs, int> execute(const t_vecIns& instructions);
    };
}

#endif
