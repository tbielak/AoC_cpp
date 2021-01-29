#include "../shared/Engine.h"
#include "2015_puzzles.h"

const AoC::t_names names = {
    { 1, "--- Day 1: Not Quite Lisp ---" },
    { 2, "--- Day 2: I Was Told There Would Be No Math ---" },
    { 3, "--- Day 3: Perfectly Spherical Houses in a Vacuum ---" },
    { 4, "--- Day 4: The Ideal Stocking Stuffer ---" },
    { 5, "--- Day 5: Doesn't He Have Intern-Elves For This? ---" },
    { 6, "--- Day 6: Probably a Fire Hazard ---" },
    { 7, "--- Day 7: Some Assembly Required ---" }
};

const AoC::t_repository repo = {
    { 1, {2, { { "", Day01_2015::main } } } },
    { 2, {2, { { "", Day02_2015::main } } } },
    { 3, {2, { { "", Day03_2015::main } } } },
    { 4, {2, { { "standard", Day04_2015::main } , { "multithreaded{T}", Day04_2015_MT::main }
    #ifdef INCLUDE_CUDA
    , { "CUDA kernel routine{C}", Day04_2015_CUDA::main }
    #endif
    } } },
    { 5, {2, { { "", Day05_2015::main } } } },
    { 6, {2, { { "", Day06_2015::main } } } },
    { 7, {2, { { "", Day07_2015::main } } } }
};

int main(int argc, char* argv[])
{
    AoC::Engine engine(2015, names, repo);
    return engine.run(argc, argv);
}
