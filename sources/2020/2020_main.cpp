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
    { 16, "--- Day 16: Ticket Translation ---" },
    { 17, "--- Day 17: Conway Cubes ---" },
    { 18, "--- Day 18: Operation Order ---" },
    { 19, "--- Day 19: Monster Messages ---" },
    { 20, "--- Day 20: Jurassic Jigsaw ---" },
    { 21, "--- Day 21: Allergen Assessment ---" },
    { 22, "--- Day 22: Crab Combat ---" },
    { 23, "--- Day 23: Crab Cups ---" },
    { 24, "--- Day 24: Lobby Layout ---" },
    { 25, "--- Day 25: Combo Breaker ---" }
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
    { 16, {2, { { "", Day16_2020::main } } } },
    { 17, {2, { { "", Day17_2020::main } } } },
    { 18, {2, { { "Shunting-yard algorithm", Day18_2020::main } , { "LALR(1) grammar parser", Day18_2020_LALR::main } } } },
    { 19, {2, { { "", Day19_2020::main } } } },
    { 20, {2, { { "", Day20_2020::main } } } },
    { 21, {2, { { "", Day21_2020::main } } } },
    { 22, {2, { { "", Day22_2020::main } } } },
    { 23, {2, { { "", Day23_2020::main } } } },
    { 24, {2, { { "", Day24_2020::main } } } },
    { 25, {2, { { "", Day25_2020::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2020, names, repo);
    return engine.run(argc, argv);
}
