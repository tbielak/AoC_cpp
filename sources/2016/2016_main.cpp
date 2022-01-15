#include "../shared/Engine.h"
#include "2016_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: No Time for a Taxicab ---" },
    { 2, "--- Day 2: Bathroom Security ---" },
    { 3, "--- Day 3: Squares With Three Sides ---" },
    { 4, "--- Day 4: Security Through Obscurity ---" },
    { 5, "--- Day 5: How About a Nice Game of Chess? ---" },
    { 6, "--- Day 6: Signals and Noise ---" },
    { 7, "--- Day 7: Internet Protocol Version 7 ---"},
    { 8, "--- Day 8: Two-Factor Authentication ---" },
    { 9, "--- Day 9: Explosives in Cyberspace ---" },
    { 10, "--- Day 10: Balance Bots ---" },
    { 11, "--- Day 11: Radioisotope Thermoelectric Generators ---" },
    { 12, "--- Day 12: Leonardo's Monorail ---" },
    { 13, "--- Day 13: A Maze of Twisty Little Cubicles ---" },
    { 14, "--- Day 14: One-Time Pad ---" },
    { 15, "--- Day 15: Timing is Everything ---" },
    { 16, "--- Day 16: Dragon Checksum ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2016::main } } } },
    { 2, {2, { { "", Day02_2016::main } } } },
    { 3, {2, { { "", Day03_2016::main } } } },
    { 4, {2, { { "", Day04_2016::main } } } },
    { 5, {2, { { "multithreaded{T}", Day05_2016::main } } } },
    { 6, {2, { { "", Day06_2016::main } } } },
    { 7, {2, { { "", Day07_2016::main } } } },
    { 8, {2, { { "", Day08_2016::main } } } },
    { 9, {2, { { "", Day09_2016::main } } } },
    { 10, {2, { { "", Day10_2016::main } } } },
    { 11, {2, { { "", Day11_2016::main } } } },
    { 12, {2, { { "", Day12_2016::main } } } },
    { 13, {2, { { "", Day13_2016::main } } } },
    { 14, {2, { { "", Day14_2016::main } } } },
    { 15, {2, { { "", Day15_2016::main } } } },
    { 16, {2, { { "", Day16_2016::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2016, names, repo);
    return engine.run(argc, argv);
}
