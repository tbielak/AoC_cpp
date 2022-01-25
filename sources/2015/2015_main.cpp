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
	{ 1, {2, { { "", new Day01_2015::Main() } } } },
	{ 2, {2, { { "", new Day02_2015::Main() } } } },
	{ 3, {2, { { "", new Day03_2015::Main() } } } },
	{ 4, {2, { { "standard", new Day04_2015::Main() } , { "multithreaded{T}", new Day04_2015_MT::Main() }
	#ifdef INCLUDE_CUDA
	, { "CUDA kernel routine{C}", new Day04_2015_CUDA::Main() }
	#endif
	} } },
	{ 5, {2, { { "", new Day05_2015::Main() } } } },
	{ 6, {2, { { "", new Day06_2015::Main() } } } },
	{ 7, {2, { { "", new Day07_2015::Main() } } } },
	{ 8, {2, { { "", new Day08_2015::Main() } } } },
	{ 9, {2, { { "", new Day09_2015::Main() } } } },
	{ 10, {2, { { "", new Day10_2015::Main() } } } },
	{ 11, {2, { { "", new Day11_2015::Main() } } } },
	{ 12, {2, { { "", new Day12_2015::Main() } } } },
	{ 13, {2, { { "", new Day13_2015::Main() } } } },
	{ 14, {2, { { "", new Day14_2015::Main() } } } },
	{ 15, {2, { { "", new Day15_2015::Main() } } } },
	{ 16, {2, { { "", new Day16_2015::Main() } } } },
	{ 17, {2, { { "", new Day17_2015::Main() } } } },
	{ 18, {2, { { "", new Day18_2015::Main() } } } },
	{ 19, {2, { { "", new Day19_2015::Main() } } } },
	{ 20, {2, { { "", new Day20_2015::Main() } } } },
	{ 21, {2, { { "", new Day21_2015::Main() } } } },
	{ 22, {2, { { "", new Day22_2015::Main() } } } },
	{ 23, {2, { { "", new Day23_2015::Main() } } } },
	#ifdef INCLUDE_CUDA
	{ 24, {2, { { "standard", new Day24_2015::Main() } , { "CUDA kernel routine{C}", new Day24_2015_CUDA::Main() } } } },
	#else
	{ 24, {2, { { "", new Day24_2015::Main() } } } },
	#endif
	{ 25, {2, { { "", new Day25_2015::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2015, names, repo);
	return engine.run(argc, argv);
}
