#include "2017_24.h"

namespace Day24_2017
{
	t_components Main::load(const vector<string>& input)
	{
		t_components components;
		for (const auto& s : input)
		{
			size_t pos = s.find_first_of('/');
			int left = stoi(s.substr(0, pos));
			int right = stoi(s.substr(pos + 1));
			components[left][right] = false;
			components[right][left] = false;
		}

		return components;
	}

	void Main::recursive_check(t_components& components, int current, int strength, int length, int& max_strength, int& max_length)
	{
		if (length > max_length)
		{
			max_strength = 0;
			max_length = length;
		}

		if (max_length == INT_MAX || length == max_length)
			max_strength = max(max_strength, strength);

		t_components::const_iterator it = components.find(current);
		if (it == components.end())
			return;

		for (const auto& [destination, visited] : it->second)
		{
			if (visited)
				continue;

			length++;
			int add_strength = current + destination;
			strength += add_strength;
			components[current][destination] = true;
			components[destination][current] = true;
			recursive_check(components, destination, strength, length, max_strength, max_length);
			components[current][destination] = false;
			components[destination][current] = false;
			strength -= add_strength;
			length--;
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto components = load(input);
		int max_strength = 0;
		int max_length = 0;
		recursive_check(components, 0, 0, INT_MAX, max_strength, max_length);
		return max_strength;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto components = load(input);
		int max_strength = 0;
		int max_length = 0;
		recursive_check(components, 0, 0, 0, max_strength, max_length);
		return max_strength;
	}
}
