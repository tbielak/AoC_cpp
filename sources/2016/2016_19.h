#ifndef __2016_19__
#define __2016_19__

#include "../shared/Solution.h"

namespace Day19_2016
{
	class Elf
	{
	public:
		int id;
		Elf* prev;
		Elf* next;
	};

	typedef vector<Elf> t_elves;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
