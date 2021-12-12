#include "../shared/Engine.h"
#include "2021_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Sonar Sweep ---" },
    { 2, "--- Day 2: Dive! ---" },
    { 3, "--- Day 3: Binary Diagnostic ---" },
    { 4, "--- Day 4: Giant Squid ---" },
    { 5, "--- Day 5: Hydrothermal Venture ---"},
    { 6, "--- Day 6: Lanternfish ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2021::main } } } },
    { 2, {2, { { "", Day02_2021::main } } } },
    { 3, {2, { { "", Day03_2021::main } } } },
    { 4, {2, { { "", Day04_2021::main } } } },
    { 5, {2, { { "", Day05_2021::main } } } },
    { 6, {2, { { "", Day06_2021::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2021, names, repo);
    return engine.run(argc, argv);
}
