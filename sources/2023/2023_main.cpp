#include "../shared/Engine.h"
#include "2023_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Trebuchet?! ---" },
	{ 2, "--- Day 2: Cube Conundrum ---" },
	{ 3, "--- Day 3: Gear Ratios ---" },
	{ 4, "--- Day 4: Scratchcards ---" },
	{ 5, "--- Day 5: If You Give A Seed A Fertilizer ---" },
	{ 6, "--- Day 6: Wait For It ---" },
	{ 7, "--- Day 7: Camel Cards ---" },
	{ 8, "--- Day 8: Haunted Wasteland ---" },
	{ 9, "--- Day 9: Mirage Maintenance ---" },
	{ 10, "--- Day 10: Pipe Maze ---" },
	{ 11, "--- Day 11: Cosmic Expansion ---" },
	{ 12, "--- Day 12: Hot Springs ---" },
	{ 13, "--- Day 13: Point of Incidence ---" },
	{ 14, "--- Day 14: Parabolic Reflector Dish ---" },
	{ 15, "--- Day 15: Lens Library ---" },
	{ 16, "--- Day 16: The Floor Will Be Lava ---" },
	{ 17, "--- Day 17: Clumsy Crucible ---" },
	{ 18, "--- Day 18: Lavaduct Lagoon ---" },
	{ 19, "--- Day 19: Aplenty ---" },
	{ 20, "--- Day 20: Pulse Propagation ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2023::Main() } } } },
	{ 2, {2, { { "", new Day02_2023::Main() } } } },
	{ 3, {2, { { "", new Day03_2023::Main() } } } },
	{ 4, {2, { { "", new Day04_2023::Main() } } } },
	{ 5, {2, { { "", new Day05_2023::Main() } } } },
	{ 6, {2, { { "", new Day06_2023::Main() } } } },
	{ 7, {2, { { "", new Day07_2023::Main() } } } },
	{ 8, {2, { { "", new Day08_2023::Main() } } } },
	{ 9, {2, { { "", new Day09_2023::Main() } } } },
	{ 10, {2, { { "", new Day10_2023::Main() } } } },
	{ 11, {2, { { "", new Day11_2023::Main() } } } },
	{ 12, {2, { { "", new Day12_2023::Main() } } } },
	{ 13, {2, { { "", new Day13_2023::Main() } } } },
	{ 14, {2, { { "", new Day14_2023::Main() } } } },
	{ 15, {2, { { "", new Day15_2023::Main() } } } },
	{ 16, {2, { { "", new Day16_2023::Main() } } } },
	{ 17, {2, { { "", new Day17_2023::Main() } } } },
	{ 18, {2, { { "", new Day18_2023::Main() } } } },
	{ 19, {2, { { "", new Day19_2023::Main() } } } },
	{ 20, {2, { { "", new Day20_2023::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2023, names, repo);
	return engine.run(argc, argv);
}
