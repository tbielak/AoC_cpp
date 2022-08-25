#include "2018_14.h"

namespace Day14_2018
{
	HotChocolate::HotChocolate()
	:	_recipe("37"), _elf1_pos(0), _elf2_pos(1)
	{
	}

	string HotChocolate::ten_recipes(size_t steps)
	{
		while (_recipe.size() < steps + 10)
			process();

		return _recipe.substr(steps, 10);
	}

	size_t HotChocolate::how_many_recipes(const string& input)
	{
		size_t steps = 0;
		while (_recipe.substr(steps, input.size()) != input)
		{
			process();
			steps++;
		}

		return steps;
	}

	void HotChocolate::process()
	{
		_recipe += to_string(int(_recipe[_elf1_pos] - '0') + int(_recipe[_elf2_pos] - '0'));
		_elf1_pos = (_elf1_pos + int(_recipe[_elf1_pos] - '0') + 1) % int(_recipe.size());
		_elf2_pos = (_elf2_pos + int(_recipe[_elf2_pos] - '0') + 1) % int(_recipe.size());
	}
	
	AoC::Output Main::part_one(const string& input)
	{
		return HotChocolate().ten_recipes(stoi(input));
	}

	AoC::Output Main::part_two(const string& input)
	{
		return HotChocolate().how_many_recipes(input);
	}
}
