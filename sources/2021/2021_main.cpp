#include "../shared/Engine.h"
#include "2021_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Sonar Sweep ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2021::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2021, names, repo);
    return engine.run(argc, argv);
}
