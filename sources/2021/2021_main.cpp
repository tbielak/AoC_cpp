#include "../shared/Engine.h"
#include "2021_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Sonar Sweep ---" },
    { 2, "--- Day 2: Dive! ---" },
    { 3, "--- Day 3: Binary Diagnostic ---" },
    { 4, "--- Day 4: Giant Squid ---" },
    { 5, "--- Day 5: Hydrothermal Venture ---" },
    { 6, "--- Day 6: Lanternfish ---" },
    { 7, "--- Day 7: The Treachery of Whales ---" },
    { 8, "--- Day 8: Seven Segment Search ---" },
    { 9, "--- Day 9: Smoke Basin ---" },
    { 10, "--- Day 10: Syntax Scoring ---" },
    { 11, "--- Day 11: Dumbo Octopus ---" },
    { 12, "--- Day 12: Passage Pathing ---" },
    { 13, "--- Day 13: Transparent Origami ---" },
    { 14, "--- Day 14: Extended Polymerization ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2021::main } } } },
    { 2, {2, { { "", Day02_2021::main } } } },
    { 3, {2, { { "", Day03_2021::main } } } },
    { 4, {2, { { "", Day04_2021::main } } } },
    { 5, {2, { { "", Day05_2021::main } } } },
    { 6, {2, { { "", Day06_2021::main } } } },
    { 7, {2, { { "", Day07_2021::main } } } },
    { 8, {2, { { "", Day08_2021::main } } } },
    { 9, {2, { { "", Day09_2021::main } } } },
    { 10, {2, { { "", Day10_2021::main } } } },
    { 11, {2, { { "", Day11_2021::main } } } },
    { 12, {2, { { "", Day12_2021::main } } } },
    { 13, {2, { { "", Day13_2021::main } } } },
    { 14, {2, { { "", Day14_2021::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2021, names, repo);
    return engine.run(argc, argv);
}
