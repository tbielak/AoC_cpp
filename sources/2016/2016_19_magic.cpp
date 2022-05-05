#include "2016_19_magic.h"

namespace Day19_2016_Magic
{
	// see: https://www.youtube.com/watch?v=uCsD3ZGzMgE#t=666
	AoC::Output Main::part_one(const string& input)
	{
		int elf_count = stoi(input);
		string binary = bitset<32>(elf_count).to_string();
		return (int)(bitset<32>(binary.substr(binary.find_first_of('1') + 1) + '1').to_ulong());
	}

	// magic :)
	AoC::Output Main::part_two(const string& input)
	{
		int elf_count = stoi(input);

		int i = 1;
		while (i * 3 < elf_count)
			i *= 3;

		return elf_count - i;
	}
}
