#include "2020_14.h"

namespace Day14_2020
{
	Instruction::Instruction(uint64_t address, uint64_t value)
	:	store(true), address(address), value(value)
	{
		or_mask[0] = 0;
		or_mask[1] = 0;
		and_mask[0] = 0;
		and_mask[1] = 0;
	}

	Instruction::Instruction(uint64_t p1or, uint64_t p1and, uint64_t p2or, uint64_t p2and)
	:	store(false), address(0), value(0)
	{
		or_mask[0] = p1or;
		or_mask[1] = p2or;
		and_mask[0] = p1and;
		and_mask[1] = p2and;
	}

	InitializationProgram::InitializationProgram(const vector<string>& input)
	{
		regex regex("mask = (.*)|mem\\[([0-9]*)\\] = ([0-9]*)");
		for (const auto& s : input)
		{
			smatch matches;
			regex_search(s, matches, regex);
			if (matches[1].str().size() == 0)
				_code.push_back(Instruction(stoi(matches[2].str()), stoi(matches[3].str())));
			else
			{
				uint64_t p1_or_mask = 0;
				uint64_t p1_and_mask = 0;
				uint64_t p2_or_mask = 0;
				uint64_t p2_and_mask = 0;
				for (auto c : matches[1].str())
				{
					p1_or_mask <<= 1;
					p1_and_mask <<= 1;
					p2_or_mask <<= 1;
					p2_and_mask <<= 1;
					if (c == 'X')
						p1_and_mask |= 1;
					if (c == '1')
					{
						p1_and_mask |= 1;
						p1_or_mask |= 1;
						p2_and_mask |= 1;
						p2_or_mask |= 1;
					}
					if (c == '0')
						p2_and_mask |= 1;
				}

				_code.push_back(Instruction(p1_or_mask, p1_and_mask, p2_or_mask, p2_and_mask));
			}
		}
	}

	uint64_t InitializationProgram::execute(size_t mask_index, void(*store_function)(t_memory&, uint64_t, uint64_t, uint64_t, uint64_t)) const
	{
		uint64_t and_mask = 0;
		uint64_t or_mask = 0;
		t_memory memory;

		for (const auto& i : _code)
		{
			if (i.store)
				store_function(memory, i.address, i.value, and_mask, or_mask);
			else
			{
				and_mask = i.and_mask[mask_index];
				or_mask = i.or_mask[mask_index];
			}
		}

		uint64_t sum = 0;
		for (const auto& m : memory)
			sum += m.second;

		return sum;
	}

	void store_part_one(t_memory& memory,
		uint64_t address, uint64_t value, uint64_t and_mask, uint64_t or_mask)
	{
		memory[address] = (value & and_mask) | or_mask;
	}

	void store_part_two(t_memory& memory,
		uint64_t address, uint64_t value, uint64_t and_mask, uint64_t or_mask)
	{
		address = (address & and_mask) | or_mask;
		uint64_t fmask = and_mask ^ 0xFFFFFFFFFL;
		uint64_t v = fmask;

		size_t count = 0;
		for (size_t i = 0; i < 36; i++)
		{
			if (v & 1)
				count++;

			v >>= 1;
		}

		vector<uint64_t> shlv(count);
		v = fmask;
		size_t j = 0;
		for (size_t i = 0; i < 36; i++)
		{
			if (v & 1)
				shlv[j++] = uint64_t(1) << uint64_t(i);

			v >>= 1;
		}

		vector<int> ctr(count);
		size_t lcount = size_t(1) << size_t(count);
		for (size_t i = 0; i < lcount; i++)
		{
			uint64_t dst = address;
			for (size_t j = 0; j < count; j++)
				if (ctr[j])
					dst |= shlv[j];

			memory[dst] = value;

			size_t j = 0;
			while (1)
			{
				ctr[j]++;
				if (ctr[j] == 2)
				{
					ctr[j++] = 0;
					if (j == count)
						break;
				}
				else
					break;
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return InitializationProgram(input).execute(0, store_part_one);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return InitializationProgram(input).execute(1, store_part_two);
	}
}
