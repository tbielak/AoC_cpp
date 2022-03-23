#include "2017_13.h"

namespace Day13_2017
{
	t_firewall Main::load(const vector<string>& input)
	{
		t_firewall firewall;
		for (const string& s : input)
		{
			size_t pos = s.find_first_of(":");
			firewall[stoi(s.substr(0, pos))] = stoi(s.substr(pos + 2));
		}

		return firewall;
	}

	bool Main::safe(int layer, int range, int delay /* = 0 */)
	{
		int cycle = (range - 1) * 2;
		return ((layer + delay) % cycle) > 0;
	}

	bool Main::safe(const t_firewall& firewall, int delay)
	{
		for (const auto& [layer, range] : firewall)
			if (!safe(layer, range, delay))
				return false;

		return true;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto firewall = load(input);

		int severity = 0;
		for (const auto& [layer, range] : firewall)
			if (!safe(layer, range))
				severity += layer * range;

		return severity;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto firewall = load(input);

		for (int delay = 0; ; delay++)
			if (safe(firewall, delay))
				return delay;

		return -1;
	}
}
