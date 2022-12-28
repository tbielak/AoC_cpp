#include "../shared/Engine.h"
#include "2022_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Calorie Counting ---" },
	{ 2, "--- Day 2: Rock Paper Scissors ---" },
	{ 3, "--- Day 3: Rucksack Reorganization ---" },
	{ 4, "--- Day 4: Camp Cleanup ---" },
	{ 5, "--- Day 5: Supply Stacks ---" },
	{ 6, "--- Day 6: Tuning Trouble ---" },
	{ 7, "--- Day 7: No Space Left On Device ---"},
	{ 8, "--- Day 8: Treetop Tree House ---" },
	{ 9, "--- Day 9: Rope Bridge ---" },
	{ 10, "--- Day 10: Cathode-Ray Tube ---" },
	{ 11, "--- Day 11: Monkey in the Middle ---" },
	{ 12, "--- Day 12: Hill Climbing Algorithm ---" },
	{ 13, "--- Day 13: Distress Signal ---" },
	{ 14, "--- Day 14: Regolith Reservoir ---" },
	{ 15, "--- Day 15: Beacon Exclusion Zone ---" },
	{ 16, "--- Day 16: Proboscidea Volcanium ---" },
	{ 17, "--- Day 17: Pyroclastic Flow ---" },
	{ 18, "--- Day 18: Boiling Boulders ---" },
	{ 19, "--- Day 19: Not Enough Minerals ---" },
	{ 20, "--- Day 20: Grove Positioning System ---" },
	{ 21, "--- Day 21: Monkey Math ---" },
	{ 22, "--- Day 22: Monkey Map ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2022::Main() } } } },
	{ 2, {2, { { "", new Day02_2022::Main() } } } },
	{ 3, {2, { { "", new Day03_2022::Main() } } } },
	{ 4, {2, { { "", new Day04_2022::Main() } } } },
	{ 5, {2, { { "", new Day05_2022::Main() } } } },
	{ 6, {2, { { "", new Day06_2022::Main() } } } },
	{ 7, {2, { { "", new Day07_2022::Main() } } } },
	{ 8, {2, { { "", new Day08_2022::Main() } } } },
	{ 9, {2, { { "", new Day09_2022::Main() } } } },
	{ 10, {2, { { "", new Day10_2022::Main() } } } },
	{ 11, {2, { { "nice C++", new Day11_2022::Main() } , { "closer to C", new Day11_2022_Alt::Main() } } } },
	{ 12, {2, { { "standard", new Day12_2022::Main() } , { "multithreaded{T}", new Day12_2022_MT::Main() } } } },
	{ 13, {2, { { "", new Day13_2022::Main() } } } },
	{ 14, {2, { { "", new Day14_2022::Main() } } } },
	{ 15, {2, { { "", new Day15_2022::Main() } } } },
	{ 16, {2, { { "", new Day16_2022::Main() } } } },
	{ 17, {2, { { "", new Day17_2022::Main() } } } },
	{ 18, {2, { { "", new Day18_2022::Main() } } } },
	{ 19, {2, { { "", new Day19_2022::Main() } } } },
	{ 20, {2, { { "", new Day20_2022::Main() } } } },
	{ 21, {2, { { "", new Day21_2022::Main() } } } },
	{ 22, {2, { { "", new Day22_2022::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2022, names, repo);
	return engine.run(argc, argv);
}
