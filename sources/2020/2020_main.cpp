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
    { 8, "--- Day 8: Handheld Halting ---" },
    { 9, "--- Day 9: Encoding Error ---" },
    { 10, "--- Day 10: Adapter Array ---" },
    { 11, "--- Day 11: Seating System ---" },
    { 12, "--- Day 12: Rain Risk ---" },
    { 13, "--- Day 13: Shuttle Search ---" },
    { 14, "--- Day 14: Docking Data ---" },
    { 15, "--- Day 15: Rambunctious Recitation ---" },
    { 16, "--- Day 16: Ticket Translation ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2020::main } } } },
    { 2, {2, { { "", Day02_2020::main } } } },
    { 3, {2, { { "", Day03_2020::main } } } },
    { 4, {2, { { "", Day04_2020::main } } } },
    { 5, {2, { { "", Day05_2020::main } } } },
    { 6, {2, { { "", Day06_2020::main } } } },
    { 7, {2, { { "", Day07_2020::main } } } },
    { 8, {2, { { "", Day08_2020::main } } } },
    { 9, {2, { { "", Day09_2020::main } } } },
    { 10, {2, { { "", Day10_2020::main } } } },
    { 11, {2, { { "", Day11_2020::main } } } },
    { 12, {2, { { "", Day12_2020::main } } } },
    { 13, {2, { { "", Day13_2020::main } } } },
    { 14, {2, { { "", Day14_2020::main } } } },
    { 15, {2, { { "", Day15_2020::main } } } },
    { 16, {2, { { "", Day16_2020::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2020, names, repo);
    return engine.run(argc, argv);
}
