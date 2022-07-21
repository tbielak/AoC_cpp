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
    { 14, "--- Day 14: Extended Polymerization ---" },
    { 15, "--- Day 15: Chiton ---" },
    { 16, "--- Day 16: Packet Decoder ---" },
    { 17, "--- Day 17: Trick Shot ---" },
    { 18, "--- Day 18: Snailfish ---" },
    { 19, "--- Day 19: Beacon Scanner ---" },
    { 20, "--- Day 20: Trench Map ---" },
    { 21, "--- Day 21: Dirac Dice ---" },
    { 22, "--- Day 22: Reactor Reboot ---" },
    { 23, "--- Day 23: Amphipod ---" },
    { 24, "--- Day 24: Arithmetic Logic Unit ---" },
    { 25, "--- Day 25: Sea Cucumber ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", new Day01_2021::Main() } } } },
    { 2, {2, { { "", new Day02_2021::Main() } } } },
    { 3, {2, { { "", new Day03_2021::Main() } } } },
    { 4, {2, { { "", new Day04_2021::Main() } } } },
    { 5, {2, { { "", new Day05_2021::Main() } } } },
    { 6, {2, { { "", new Day06_2021::Main() } } } },
    { 7, {2, { { "", new Day07_2021::Main() } } } },
    { 8, {2, { { "", new Day08_2021::Main() } } } },
    { 9, {2, { { "", new Day09_2021::Main() } } } },
    { 10, {2, { { "", new Day10_2021::Main() } } } },
    { 11, {2, { { "", new Day11_2021::Main() } } } },
    { 12, {2, { { "", new Day12_2021::Main() } } } },
    { 13, {2, { { "", new Day13_2021::Main() } } } },
    { 14, {2, { { "", new Day14_2021::Main() } } } },
    { 15, {2, { { "", new Day15_2021::Main() } } } },
    { 16, {2, { { "", new Day16_2021::Main() } } } },
    { 17, {2, { { "", new Day17_2021::Main() } } } },
    { 18, {2, { { "strings", new Day18_2021_Strings::Main() } , { "pairs", new Day18_2021_Pairs::Main() } } } },
    { 19, {2, { { "", new Day19_2021::Main() } } } },
    { 20, {2, { { "", new Day20_2021::Main() } } } },
    { 21, {2, { { "", new Day21_2021::Main() } } } },
    { 22, {2, { { "", new Day22_2021::Main() } } } },
    { 23, {2, { { "", new Day23_2021::Main() } } } },
    { 24, {2, { { "", new Day24_2021::Main() } } } },
    { 25, {2, { { "", new Day25_2021::Main() } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2021, names, repo);
    return engine.run(argc, argv);
}
