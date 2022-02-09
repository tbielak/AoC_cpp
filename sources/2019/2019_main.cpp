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
    { 19, "--- Day 19: Tractor Beam ---" },
    { 20, "--- Day 20: Donut Maze ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", new Day01_2019::Main() } } } },
    { 2, {2, { { "", new Day02_2019::Main() } } } },
    { 3, {2, { { "", new Day03_2019::Main() } } } },
    { 4, {2, { { "", new Day04_2019::Main() } } } },
    { 5, {2, { { "", new Day05_2019::Main() } } } },
    { 6, {2, { { "", new Day06_2019::Main() } } } },
    { 7, {2, { { "", new Day07_2019::Main() } } } },
    { 8, {2, { { "", new Day08_2019::Main() } } } },
    { 9, {2, { { "", new Day09_2019::Main() } } } },
    { 10, {2, { { "", new Day10_2019::Main() } } } },
    { 11, {2, { { "", new Day11_2019::Main() } } } },
    { 12, {2, { { "", new Day12_2019::Main() } } } },
    { 13, {2, { { "", new Day13_2019::Main() } } } },
    { 14, {2, { { "", new Day14_2019::Main() } } } },
    { 15, {2, { { "", new Day15_2019::Main() } } } },
    { 16, {2, { { "", new Day16_2019::Main() } } } },
    { 17, {2, { { "", new Day17_2019::Main() } } } },
    { 18, {2, { { "", new Day18_2019::Main() } } } },
    { 19, {2, { { "", new Day19_2019::Main() } } } },
    { 20, {2, { { "", new Day20_2019::Main() } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2019, names, repo);
    return engine.run(argc, argv);
}
