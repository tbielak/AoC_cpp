#include "../shared/Engine.h"
#include "2020_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Report Repair ---" },
    { 2, "--- Day 2: Password Philosophy ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2020::main } } } },
    { 2, {2, { { "", Day02_2020::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2020, names, repo);
    return engine.run(argc, argv);
}
