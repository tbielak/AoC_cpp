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
	{ 14, "--- Day 14: Restroom Redoubt ---" },
	{ 15, "--- Day 15: Warehouse Woes ---" },
	{ 16, "--- Day 16: Reindeer Maze ---" },
	{ 17, "--- Day 17: Chronospatial Computer ---" },
	{ 18, "--- Day 18: RAM Run ---" },
	{ 19, "--- Day 19: Linen Layout ---" },
	{ 20, "--- Day 20: Race Condition ---" },
	{ 21, "--- Day 21: Keypad Conundrum ---" },
	{ 22, "--- Day 22: Monkey Market ---" },
	{ 23, "--- Day 23: LAN Party ---" },
	{ 24, "--- Day 24: Crossed Wires ---" },
	{ 25, "--- Day 25: Code Chronicle ---" }
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
	{ 14, {2, { { "", new Day14_2024::Main() } } } },
	{ 15, {2, { { "", new Day15_2024::Main() } } } },
	{ 16, {2, { { "", new Day16_2024::Main() } } } },
	{ 17, {2, { { "", new Day17_2024::Main() } } } },
	{ 18, {2, { { "", new Day18_2024::Main() } } } },
	{ 19, {2, { { "", new Day19_2024::Main() } } } },
	{ 20, {2, { { "", new Day20_2024::Main() } } } },
	{ 21, {2, { { "", new Day21_2024::Main() } } } },
	{ 22, {2, { { "", new Day22_2024::Main() } } } },
	{ 23, {2, { { "", new Day23_2024::Main() } } } },
	{ 24, {2, { { "", new Day24_2024::Main() } } } },
	{ 25, {2, { { "", new Day25_2024::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2024, names, repo);
	return engine.run(argc, argv);
}
