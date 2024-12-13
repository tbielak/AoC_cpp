#include "2024_11.h"

namespace Day11_2024
{
	StoneCounter::StoneCounter(const string& input)
	{
		string s;
		stringstream ss(input);
		while (getline(ss, s, ' '))
			_data[stoll(s)] = 1;
	}

	const StoneCounter& StoneCounter::blink(int steps)
	{
		for (int i = 0; i < steps; i++)
		{
			auto input = move(_data);
			_data.clear();

			for (auto [value, count] : input)
			{
				if (value == 0)
					_data[1] = count;
				else
				{
					string s = to_string(value);
					if ((s.size() & 1) == 0)
					{
						_data[stoll(s.substr(0, s.size() / 2))] += count;
						_data[stoll(s.substr(s.size() / 2))] += count;
					}
					else
						_data[value * 2024] += count;
				}
			}
		}

		return *this;
	}

	int64_t StoneCounter::count() const
	{
		int64_t sum = 0;
		for (auto [_, count] : _data)
			sum += count;

		return sum;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return StoneCounter(input).blink(25).count();
	}

	AoC::Output Main::part_two(const string& input)
	{
		return StoneCounter(input).blink(75).count();
	}
}
