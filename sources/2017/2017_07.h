#ifndef __2017_07__
#define __2017_07__

#include "../shared/Solution.h"

namespace Day07_2017
{
    class Program;
    typedef vector<Program*> t_vecptrProgram;

    class Program
    {
    public:
        Program(const string& name);

        int count() const;

        int recursive_weight() const;

        string name;
        int weight;
        int tree_weight;
        t_vecptrProgram above;
    };

    typedef map<string, Program*> t_mapptrProgram;

    class Tower
    {
    public:
        Tower(const vector<string>& input);

        string bottom_name() const;
        int weight_correction() const;

    private:
        t_mapptrProgram _programs;
        t_mapptrProgram::const_iterator _bottom;

        Program* add(const string& name);
    };

    class Main : public AoC::Solution
    {
    public:
        virtual AoC::Output part_one(const vector<string>& input);
        virtual AoC::Output part_two(const vector<string>& input);
    };
}

#endif
