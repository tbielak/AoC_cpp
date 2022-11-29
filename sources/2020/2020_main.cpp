#include "../shared/Engine.h"
#include "2020_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Report Repair ---" },
	{ 2, "--- Day 2: Password Philosophy ---" },
	{ 3, "--- Day 3: Toboggan Trajectory ---" },
	{ 4, "--- Day 4: Passport Processing ---" },
	{ 5, "--- Day 5: Binary Boarding ---" },
	{ 6, "--- Day 6: Custom Customs ---" },
	{ 7, "--- Day 7: Handy Haversacks ---" },
	{ 8, "--- Day 8: Handheld Halting ---" },
	{ 9, "--- Day 9: Encoding Error ---" },
	{ 10, "--- Day 10: Adapter Array ---" },
	{ 11, "--- Day 11: Seating System ---" },
	{ 12, "--- Day 12: Rain Risk ---" },
	{ 13, "--- Day 13: Shuttle Search ---" },
	{ 14, "--- Day 14: Docking Data ---" },
	{ 15, "--- Day 15: Rambunctious Recitation ---" },
	{ 16, "--- Day 16: Ticket Translation ---" },
	{ 17, "--- Day 17: Conway Cubes ---" },
	{ 18, "--- Day 18: Operation Order ---" },
	{ 19, "--- Day 19: Monster Messages ---" },
	{ 20, "--- Day 20: Jurassic Jigsaw ---" },
	{ 21, "--- Day 21: Allergen Assessment ---" },
	{ 22, "--- Day 22: Crab Combat ---" },
	{ 23, "--- Day 23: Crab Cups ---" },
	{ 24, "--- Day 24: Lobby Layout ---" },
	{ 25, "--- Day 25: Combo Breaker ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2020::Main() } } } },
	{ 2, {2, { { "", new Day02_2020::Main() } } } },
	{ 3, {2, { { "", new Day03_2020::Main() } } } },
	{ 4, {2, { { "", new Day04_2020::Main() } } } },
	{ 5, {2, { { "", new Day05_2020::Main() } } } },
	{ 6, {2, { { "", new Day06_2020::Main() } } } },
	{ 7, {2, { { "", new Day07_2020::Main() } } } },
	{ 8, {2, { { "", new Day08_2020::Main() } } } },
	{ 9, {2, { { "", new Day09_2020::Main() } } } },
	{ 10, {2, { { "", new Day10_2020::Main() } } } },
	{ 11, {2, { { "", new Day11_2020::Main() } } } },
	{ 12, {2, { { "", new Day12_2020::Main() } } } },
	{ 13, {2, { { "", new Day13_2020::Main() } } } },
	{ 14, {2, { { "", new Day14_2020::Main() } } } },
	{ 15, {2, { { "", new Day15_2020::Main() } } } },
	{ 16, {2, { { "", new Day16_2020::Main() } } } },
	{ 17, {2, { { "", new Day17_2020::Main() } } } },
	{ 18, {2, { { "Shunting-yard algorithm", new Day18_2020::Main() } , { "LALR(1) grammar parser", new Day18_2020_LALR::Main() } } } },
	{ 19, {2, { { "", new Day19_2020::Main() } } } },
	{ 20, {2, { { "", new Day20_2020::Main() } } } },
	{ 21, {2, { { "", new Day21_2020::Main() } } } },
	{ 22, {2, { { "", new Day22_2020::Main() } } } },
	{ 23, {2, { { "", new Day23_2020::Main() } } } },
	{ 24, {2, { { "", new Day24_2020::Main() } } } },
	{ 25, {2, { { "", new Day25_2020::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2020, names, repo);
	return engine.run(argc, argv);
}
