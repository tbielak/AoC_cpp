#include "2020_14.h"

namespace Day14_2020
{
	Instruction::Instruction(uintmax_t address, uintmax_t value)
	:	store(true), address(address), value(value)
	{
		or_mask[0] = 0;
		or_mask[1] = 0;
		and_mask[0] = 0;
		and_mask[1] = 0;
	}

	Instruction::Instruction(uintmax_t p1or, uintmax_t p1and, uintmax_t p2or, uintmax_t p2and)
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
				uintmax_t p1_or_mask = 0;
				uintmax_t p1_and_mask = 0;
				uintmax_t p2_or_mask = 0;
				uintmax_t p2_and_mask = 0;
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

	uintmax_t InitializationProgram::execute(size_t mask_index, void(*store_function)(t_memory&, uintmax_t, uintmax_t, uintmax_t, uintmax_t)) const
	{
		uintmax_t and_mask = 0;
		uintmax_t or_mask = 0;
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

		uintmax_t sum = 0;
		for (const auto& m : memory)
			sum += m.second;

		return sum;
	}

	void store_part_one(t_memory& memory,
		uintmax_t address, uintmax_t value, uintmax_t and_mask, uintmax_t or_mask)
	{
		memory[address] = (value & and_mask) | or_mask;
	}

	void store_part_two(t_memory& memory,
		uintmax_t address, uintmax_t value, uintmax_t and_mask, uintmax_t or_mask)
	{
		address = (address & and_mask) | or_mask;
		uintmax_t fmask = and_mask ^ 0xFFFFFFFFFL;
		uintmax_t v = fmask;

		size_t count = 0;
		for (size_t i = 0; i < 36; i++)
		{
			if (v & 1)
				count++;

			v >>= 1;
		}

		vector<uintmax_t> shlv(count);
		v = fmask;
		size_t j = 0;
		for (size_t i = 0; i < 36; i++)
		{
			if (v & 1)
				shlv[j++] = uintmax_t(1) << uintmax_t(i);

			v >>= 1;
		}

		vector<int> ctr(count);
		size_t lcount = size_t(1) << size_t(count);
		for (size_t i = 0; i < lcount; i++)
		{
			uintmax_t dst = address;
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

	uintmax_t part_one(const InitializationProgram& program)
	{
		return program.execute(0, store_part_one);
	}

	uintmax_t part_two(const InitializationProgram& program)
	{
		return program.execute(1, store_part_two);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		InitializationProgram program(input);
		auto p1 = part_one(program);
		auto p2 = part_two(program);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
