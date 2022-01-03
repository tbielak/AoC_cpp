#include "../shared/Engine.h"
#include "2016_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: No Time for a Taxicab ---" },
    { 2, "--- Day 2: Bathroom Security ---" },
    { 3, "--- Day 3: Squares With Three Sides ---" },
    { 4, "--- Day 4: Security Through Obscurity ---" },
    { 5, "--- Day 5: How About a Nice Game of Chess? ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2016::main } } } },
    { 2, {2, { { "", Day02_2016::main } } } },
    { 3, {2, { { "", Day03_2016::main } } } },
    { 4, {2, { { "", Day04_2016::main } } } },
    { 5, {2, { { "multithreaded{T}", Day05_2016::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2016, names, repo);
    return engine.run(argc, argv);
}
