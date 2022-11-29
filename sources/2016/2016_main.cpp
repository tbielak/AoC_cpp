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
	{ 16, "--- Day 16: Dragon Checksum ---" },
	{ 17, "--- Day 17: Two Steps Forward ---" },
	{ 18, "--- Day 18: Like a Rogue ---" },
	{ 19, "--- Day 19: An Elephant Named Joseph ---" },
	{ 20, "--- Day 20: Firewall Rules ---" },
	{ 21, "--- Day 21: Scrambled Letters and Hash ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2016::Main() } } } },
	{ 2, {2, { { "", new Day02_2016::Main() } } } },
	{ 3, {2, { { "", new Day03_2016::Main() } } } },
	{ 4, {2, { { "", new Day04_2016::Main() } } } },
	{ 5, {2, { { "multithreaded{T}", new Day05_2016::Main() } } } },
	{ 6, {2, { { "", new Day06_2016::Main() } } } },
	{ 7, {2, { { "", new Day07_2016::Main() } } } },
	{ 8, {2, { { "", new Day08_2016::Main() } } } },
	{ 9, {2, { { "", new Day09_2016::Main() } } } },
	{ 10, {2, { { "", new Day10_2016::Main() } } } },
	{ 11, {2, { { "", new Day11_2016::Main() } } } },
	{ 12, {2, { { "", new Day12_2016::Main() } } } },
	{ 13, {2, { { "", new Day13_2016::Main() } } } },
	{ 14, {2, { { "", new Day14_2016::Main() } } } },
	{ 15, {2, { { "", new Day15_2016::Main() } } } },
	{ 16, {2, { { "", new Day16_2016::Main() } } } },
	{ 17, {2, { { "", new Day17_2016::Main() } } } },
	{ 18, {2, { { "", new Day18_2016::Main() } } } },
	{ 19, {2, { { "regular", new Day19_2016::Main() } , { "magic", new Day19_2016_Magic::Main() } } } },
	{ 20, {2, { { "", new Day20_2016::Main() } } } },
	{ 21, {2, { { "", new Day21_2016::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2016, names, repo);
	return engine.run(argc, argv);
}
