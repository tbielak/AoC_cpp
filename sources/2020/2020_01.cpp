#include "2020_01.h"

namespace Day01_2020
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoi(line));

		return data;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto x = load(input);

		for (auto a : x)
			for (auto b : x)
				if (2020 == a + b)
					return  a * b;

		return -1;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto x = load(input);

		for (auto a : x)
			for (auto b : x)
				for (auto c : x)
					if (2020 == a + b + c)
						return  a * b * c;

		return -1;
	}
}
