#include "../shared/Engine.h"
#include "2017_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Inverse Captcha ---" },
    { 2, "--- Day 2: Corruption Checksum ---" },
    { 3, "--- Day 3: Spiral Memory ---" },
    { 4, "--- Day 4: High-Entropy Passphrases ---" },
    { 5, "--- Day 5: A Maze of Twisty Trampolines, All Alike ---" },
    { 6, "--- Day 6: Memory Reallocation ---" },
    { 7, "--- Day 7: Recursive Circus ---" },
    { 8, "--- Day 8: I Heard You Like Registers ---" },
    { 9, "--- Day 9: Stream Processing ---" },
    { 10, "--- Day 10: Knot Hash ---" },
    { 11, "--- Day 11: Hex Ed ---" },
    { 12, "--- Day 12: Digital Plumber ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", new Day01_2017::Main() } } } },
    { 2, {2, { { "", new Day02_2017::Main() } } } },
    { 3, {2, { { "", new Day03_2017::Main() } } } },
    { 4, {2, { { "", new Day04_2017::Main() } } } },
    { 5, {2, { { "", new Day05_2017::Main() } } } },
    { 6, {2, { { "", new Day06_2017::Main() } } } },
    { 7, {2, { { "", new Day07_2017::Main() } } } },
    { 8, {2, { { "", new Day08_2017::Main() } } } },
    { 9, {2, { { "", new Day09_2017::Main() } } } },
    { 10, {2, { { "", new Day10_2017::Main() } } } },
    { 11, {2, { { "", new Day11_2017::Main() } } } },
    { 12, {2, { { "", new Day12_2017::Main() } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2017, names, repo);
    return engine.run(argc, argv);
}
