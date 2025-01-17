#include "../shared/Engine.h"
#include "2018_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Chronal Calibration ---" },
	{ 2, "--- Day 2: Inventory Management System ---" },
	{ 3, "--- Day 3: No Matter How You Slice It ---" },
	{ 4, "--- Day 4: Repose Record ---" },
	{ 5, "--- Day 5: Alchemical Reduction ---" },
	{ 6, "--- Day 6: Chronal Coordinates ---" },
	{ 7, "--- Day 7: The Sum of Its Parts ---" },
	{ 8, "--- Day 8: Memory Maneuver ---" },
	{ 9, "--- Day 9: Marble Mania ---" },
	{ 10, "--- Day 10: The Stars Align ---" },
	{ 11, "--- Day 11: Chronal Charge ---" },
	{ 12, "--- Day 12: Subterranean Sustainability ---" },
	{ 13, "--- Day 13: Mine Cart Madness ---" },
	{ 14, "--- Day 14: Chocolate Charts ---" },
	{ 15, "--- Day 15: Beverage Bandits ---" },
	{ 16, "--- Day 16: Chronal Classification ---" },
	{ 17, "--- Day 17: Reservoir Research ---" },
	{ 18, "--- Day 18: Settlers of The North Pole ---" },
	{ 19, "--- Day 19: Go With The Flow ---" },
	{ 20, "--- Day 20: A Regular Map ---" },
	{ 21, "--- Day 21: Chronal Conversion ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2018::Main() } } } },
	{ 2, {2, { { "", new Day02_2018::Main() } } } },
	{ 3, {2, { { "", new Day03_2018::Main() } } } },
	{ 4, {2, { { "", new Day04_2018::Main() } } } },
	{ 5, {2, { { "", new Day05_2018::Main() } } } },
	{ 6, {2, { { "", new Day06_2018::Main() } } } },
	{ 7, {2, { { "", new Day07_2018::Main() } } } },
	{ 8, {2, { { "", new Day08_2018::Main() } } } },
	{ 9, {2, { { "", new Day09_2018::Main() } } } },
	{ 10, {2, { { "", new Day10_2018::Main() } } } },
	{ 11, {2, { { "", new Day11_2018::Main() } } } },
	{ 12, {2, { { "", new Day12_2018::Main() } } } },
	{ 13, {2, { { "", new Day13_2018::Main() } } } },
	{ 14, {2, { { "", new Day14_2018::Main() } } } },
	{ 15, {2, { { "", new Day15_2018::Main() } } } },
	{ 16, {2, { { "", new Day16_2018::Main() } } } },
	{ 17, {2, { { "", new Day17_2018::Main() } } } },
	{ 18, {2, { { "", new Day18_2018::Main() } } } },
	{ 19, {2, { { "", new Day19_2018::Main() } } } },
	{ 20, {2, { { "", new Day20_2018::Main() } } } },
	{ 21, {2, { { "", new Day21_2018::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2018, names, repo);
	return engine.run(argc, argv);
}
