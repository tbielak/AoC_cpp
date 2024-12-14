#include "../shared/Engine.h"
#include "2024_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Historian Hysteria ---" },
	{ 2, "--- Day 2: Red-Nosed Reports ---" },
	{ 3, "--- Day 3: Mull It Over ---" },
	{ 4, "--- Day 4: Ceres Search ---" },
	{ 5, "--- Day 5: Print Queue ---" },
	{ 6, "--- Day 6: Guard Gallivant ---" },
	{ 7, "--- Day 7: Bridge Repair ---" },
	{ 8, "--- Day 8: Resonant Collinearity ---" },
	{ 9, "--- Day 9: Disk Fragmenter ---" },
	{ 10, "--- Day 10: Hoof It ---" },
	{ 11, "--- Day 11: Plutonian Pebbles ---" },
	{ 12, "--- Day 12: Garden Groups ---" },
	{ 13, "--- Day 13: Claw Contraption ---" },
	{ 14, "--- Day 14: Restroom Redoubt ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2024::Main() } } } },
	{ 2, {2, { { "", new Day02_2024::Main() } } } },
	{ 3, {2, { { "", new Day03_2024::Main() } } } },
	{ 4, {2, { { "", new Day04_2024::Main() } } } },
	{ 5, {2, { { "", new Day05_2024::Main() } } } },
	{ 6, {2, { { "", new Day06_2024::Main() } } } },
	{ 7, {2, { { "", new Day07_2024::Main() } } } },
	{ 8, {2, { { "", new Day08_2024::Main() } } } },
	{ 9, {2, { { "", new Day09_2024::Main() } } } },
	{ 10, {2, { { "", new Day10_2024::Main() } } } },
	{ 11, {2, { { "", new Day11_2024::Main() } } } },
	{ 12, {2, { { "", new Day12_2024::Main() } } } },
	{ 13, {2, { { "", new Day13_2024::Main() } } } },
	{ 14, {2, { { "", new Day14_2024::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2024, names, repo);
	return engine.run(argc, argv);
}
