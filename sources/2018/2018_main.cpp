#include "../shared/Engine.h"
#include "2018_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Chronal Calibration ---" },
    { 2, "--- Day 2: Inventory Management System ---" },
    { 3, "--- Day 3: No Matter How You Slice It ---" },
    { 4, "--- Day 4: Repose Record ---" },
    { 5, "--- Day 5: Alchemical Reduction ---" },
    { 6, "--- Day 6: Chronal Coordinates ---" },
    { 7, "--- Day 7: The Sum of Its Parts ---" },
    { 8, "--- Day 8: Memory Maneuver ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", new Day01_2018::Main() } } } },
    { 2, {2, { { "", new Day02_2018::Main() } } } },
    { 3, {2, { { "", new Day03_2018::Main() } } } },
    { 4, {2, { { "", new Day04_2018::Main() } } } },
    { 5, {2, { { "", new Day05_2018::Main() } } } },
    { 6, {2, { { "", new Day06_2018::Main() } } } },
    { 7, {2, { { "", new Day07_2018::Main() } } } },
    { 8, {2, { { "", new Day08_2018::Main() } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2018, names, repo);
    return engine.run(argc, argv);
}
