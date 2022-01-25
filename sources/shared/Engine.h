#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "stl.h"

#ifdef INCLUDE_CUDA
#include "CUDA_misc.h"
#endif

#include "Console.h"
#include "Options.h"
#include "Solution.h"

namespace AoC
{
    typedef map<int, string> t_names;

    typedef pair<string, Solution *> t_solution;
    typedef vector<t_solution> t_solutions;
    typedef map<int, pair<int, t_solutions>> t_repository;

    class Engine
    {
    public:
        Engine(int year, const t_names& names, const t_repository& repo);
        int run(int argc, char* argv[]);

    private:
        Console _cc;
        string _year;
        const t_names& _names;
        const t_repository& _repo;
        Options _options;

        void intro();
        void help();
        void available_solutions();
        bool load_input(const string& input_filename, size_t i, vector<string>& input);
        void print_output(const t_output& output, size_t count = 0);
        bool execute(bool print_info, t_output& output, const string& input_filename, int day, size_t solution);
        void execute_solution(int speed, const string& input_filename, int day, size_t solution);
        void execute_day(int speed, const string& input_filename, int day);
        void execute_all(int speed);
    };
}

#endif
