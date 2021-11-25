#include "../shared/Engine.h"
#include "2019_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: The Tyranny of the Rocket Equation ---" },
    { 2, "--- Day 2: 1202 Program Alarm ---" },
    { 3, "--- Day 3: Crossed Wires ---" },
    { 4, "--- Day 4: Secure Container ---" },
    { 5, "--- Day 5: Sunny with a Chance of Asteroids ---"},
    { 6, "--- Day 6: Universal Orbit Map ---" },
    { 7, "--- Day 7: Amplification Circuit ---" },
    { 8, "--- Day 8: Space Image Format ---" },
    { 9, "--- Day 9: Sensor Boost ---" },
    { 10, "--- Day 10: Monitoring Station ---" },
    { 11, "--- Day 11: Space Police ---" },
    { 12, "--- Day 12: The N-Body Problem ---" },
    { 13, "--- Day 13: Care Package ---" },
    { 14, "--- Day 14: Space Stoichiometry ---" },
    { 15, "--- Day 15: Oxygen System ---" },
    { 16, "--- Day 16: Flawed Frequency Transmission ---" },
    { 17, "--- Day 17: Set and Forget ---" },
    { 18, "--- Day 18: Many-Worlds Interpretation ---" },
    { 19, "--- Day 19: Tractor Beam ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2019::main } } } },
    { 2, {2, { { "", Day02_2019::main } } } },
    { 3, {2, { { "", Day03_2019::main } } } },
    { 4, {2, { { "", Day04_2019::main } } } },
    { 5, {2, { { "", Day05_2019::main } } } },
    { 6, {2, { { "", Day06_2019::main } } } },
    { 7, {2, { { "", Day07_2019::main } } } },
    { 8, {2, { { "", Day08_2019::main } } } },
    { 9, {2, { { "", Day09_2019::main } } } },
    { 10, {2, { { "", Day10_2019::main } } } },
    { 11, {2, { { "", Day11_2019::main } } } },
    { 12, {2, { { "", Day12_2019::main } } } },
    { 13, {2, { { "", Day13_2019::main } } } },
    { 14, {2, { { "", Day14_2019::main } } } },
    { 15, {2, { { "", Day15_2019::main } } } },
    { 16, {2, { { "", Day16_2019::main } } } },
    { 17, {2, { { "", Day17_2019::main } } } },
    { 18, {2, { { "", Day18_2019::main } } } },
    { 19, {2, { { "", Day19_2019::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2019, names, repo);
    return engine.run(argc, argv);
}
