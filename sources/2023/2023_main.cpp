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
	{ 8, "--- Day 8: Haunted Wasteland ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2023::Main() } } } },
	{ 2, {2, { { "", new Day02_2023::Main() } } } },
	{ 3, {2, { { "", new Day03_2023::Main() } } } },
	{ 4, {2, { { "", new Day04_2023::Main() } } } },
	{ 5, {2, { { "", new Day05_2023::Main() } } } },
	{ 6, {2, { { "", new Day06_2023::Main() } } } },
	{ 7, {2, { { "", new Day07_2023::Main() } } } },
	{ 8, {2, { { "", new Day08_2023::Main() } } } }
};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2023, names, repo);
	return engine.run(argc, argv);
}
