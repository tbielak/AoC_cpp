#include "../shared/Engine.h"
#include "2024_puzzles.h"

const AoC::t_names names = {
	{ 1, "--- Day 1: Historian Hysteria ---" },
	{ 2, "--- Day 2: Red-Nosed Reports ---" },
	{ 3, "--- Day 3: Mull It Over ---" },
	{ 4, "--- Day 4: Ceres Search ---" },
	{ 5, "--- Day 5: Print Queue ---" }
};

const AoC::t_repository repo = {
	{ 1, {2, { { "", new Day01_2024::Main() } } } },
	{ 2, {2, { { "", new Day02_2024::Main() } } } },
	{ 3, {2, { { "", new Day03_2024::Main() } } } },
	{ 4, {2, { { "", new Day04_2024::Main() } } } },
	{ 5, {2, { { "", new Day05_2024::Main() } } } }

};

int main(int argc, char* argv[])
{
	AoC::Engine engine(2024, names, repo);
	return engine.run(argc, argv);
}
