#include "2016_19.h"

namespace Day19_2016
{
	AoC::Output Main::part_one(const string& input)
	{
		int elf_count = stoi(input);

		// circle of elves having presents
		t_elves elves = t_elves(elf_count);
		for (int i = 0; i < elf_count; i++)
		{
			elves[i].id = i + 1;
			elves[i].prev = (i == 0) ? &elves[elf_count - 1] : &elves[i - 1];
			elves[i].next = (i == elf_count - 1) ? &elves[0] : &elves[i + 1];
		}

		// current one
		Elf* e = &elves[0];

		// check if only one left
		while (e->prev != e->next)
		{
			// remove one elf from a circle
			e->next = e->next->next;
			e = e->next;
			e->prev = e->prev->prev;
		}

		// last left
		return e->id;
	}

	AoC::Output Main::part_two(const string& input)
	{
		int elf_count = stoi(input);

		// make circle as two lists, each list keeps half of elfs
		list<int> a;
		for (int i = 0; i <= elf_count / 2; i++)
			a.push_back(i);

		list<int> b;
		for (int i = elf_count / 2 + 1; i <= elf_count; i++)
			b.push_back(i);

		// O(n) reduction
		// until list a has one elf and list b has zero elfs
		while (b.size() > 0)
		{
			// get first elf and remove it from the list
			int first_elf = a.front();
			a.pop_front();

			// drop elf in the middle
			if (a.size() == b.size())
				a.pop_back();
			else
				b.pop_front();

			// put first elf at the end of the circle
			b.push_back(first_elf);

			// balance lists
			a.push_back(b.front());
			b.pop_front();
		}

		// and the winner is:
		return a.front();
	}
}
