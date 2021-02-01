#include "../shared/Engine.h"
#include "2020_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Report Repair ---" },
    { 2, "--- Day 2: Password Philosophy ---" },
    { 3, "--- Day 3: Toboggan Trajectory ---" },
    { 4, "--- Day 4: Passport Processing ---" },
    { 5, "--- Day 5: Binary Boarding ---" },
    { 6, "--- Day 6: Custom Customs ---" },
    { 7, "--- Day 7: Handy Haversacks ---" },
    { 8, "--- Day 8: Handheld Halting ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2020::main } } } },
    { 2, {2, { { "", Day02_2020::main } } } },
    { 3, {2, { { "", Day03_2020::main } } } },
    { 4, {2, { { "", Day04_2020::main } } } },
    { 5, {2, { { "", Day05_2020::main } } } },
    { 6, {2, { { "", Day06_2020::main } } } },
    { 7, {2, { { "", Day07_2020::main } } } },
    { 8, {2, { { "", Day08_2020::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2020, names, repo);
    return engine.run(argc, argv);
}
