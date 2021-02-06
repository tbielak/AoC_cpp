#include "../shared/Engine.h"
#include "2015_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Not Quite Lisp ---" },
    { 2, "--- Day 2: I Was Told There Would Be No Math ---" },
    { 3, "--- Day 3: Perfectly Spherical Houses in a Vacuum ---" },
    { 4, "--- Day 4: The Ideal Stocking Stuffer ---" },
    { 5, "--- Day 5: Doesn't He Have Intern-Elves For This? ---" },
    { 6, "--- Day 6: Probably a Fire Hazard ---" },
    { 7, "--- Day 7: Some Assembly Required ---" },
    { 8, "--- Day 8: Matchsticks ---" },
    { 9, "--- Day 9: All in a Single Night ---" },
    { 10, "--- Day 10: Elves Look, Elves Say ---" },
    { 11, "--- Day 11: Corporate Policy ---" },
    { 12, "--- Day 12: JSAbacusFramework.io ---" },
    { 13, "--- Day 13: Knights of the Dinner Table ---" },
    { 14, "--- Day 14: Reindeer Olympics ---" },
    { 15, "--- Day 15: Science for Hungry People ---" },
    { 16, "--- Day 16: Aunt Sue ---" },
    { 17, "--- Day 17: No Such Thing as Too Much ---" },
    { 18, "--- Day 18: Like a GIF For Your Yard ---" },
    { 19, "--- Day 19: Medicine for Rudolph ---" },
    { 20, "--- Day 20: Infinite Elves and Infinite Houses ---" },
    { 21, "--- Day 21: RPG Simulator 20XX ---" },
    { 22, "--- Day 22: Wizard Simulator 20XX ---" },
    { 23, "--- Day 23: Opening the Turing Lock ---" },
    { 24, "--- Day 24: It Hangs in the Balance ---" },
    { 25, "--- Day 25: Let It Snow ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2015::main } } } },
    { 2, {2, { { "", Day02_2015::main } } } },
    { 3, {2, { { "", Day03_2015::main } } } },
    { 4, {2, { { "standard", Day04_2015::main } , { "multithreaded{T}", Day04_2015_MT::main }
    #ifdef INCLUDE_CUDA
    , { "CUDA kernel routine{C}", Day04_2015_CUDA::main }
    #endif
    } } },
    { 5, {2, { { "", Day05_2015::main } } } },
    { 6, {2, { { "", Day06_2015::main } } } },
    { 7, {2, { { "", Day07_2015::main } } } },
    { 8, {2, { { "", Day08_2015::main } } } },
    { 9, {2, { { "", Day09_2015::main } } } },
    { 10, {2, { { "", Day10_2015::main } } } },
    { 11, {2, { { "", Day11_2015::main } } } },
    { 12, {2, { { "", Day12_2015::main } } } },
    { 13, {2, { { "", Day13_2015::main } } } },
    { 14, {2, { { "", Day14_2015::main } } } },
    { 15, {2, { { "", Day15_2015::main } } } },
    { 16, {2, { { "", Day16_2015::main } } } },
    { 17, {2, { { "", Day17_2015::main } } } },
    { 18, {2, { { "", Day18_2015::main } } } },
    { 19, {2, { { "", Day19_2015::main } } } },
    { 20, {2, { { "", Day20_2015::main } } } },
    { 21, {2, { { "", Day21_2015::main } } } },
    { 22, {2, { { "", Day22_2015::main } } } },
    { 23, {2, { { "", Day23_2015::main } } } },
    { 24, {2, { { "standard", Day24_2015::main }
    #ifdef INCLUDE_CUDA
    , { "CUDA kernel routine{C}", Day24_2015_CUDA::main }
    #endif
    } } },
    { 25, {2, { { "", Day25_2015::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2015, names, repo);
    return engine.run(argc, argv);
}
