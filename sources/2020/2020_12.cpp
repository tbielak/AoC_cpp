#include "2020_12.h"

namespace Day12_2020
{
	t_navigation Main::load(const vector<string>& input)
	{
		t_navigation nav;
		for (const auto& line : input)
			nav.push_back(make_pair(line[0], stoi(line.substr(1))));

		return nav;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto nav = load(input);

		// d -> direction: 0 = north, 1 = west, 2 = south, 3 - east
		int x = 0;
		int y = 0;
		int d = 3;
		for (const auto& n : nav)
		{
			switch (n.first)
			{
			case 'N': y -= n.second; break;
			case 'S': y += n.second; break;
			case 'E': x += n.second; break;
			case 'W': x -= n.second; break;
			case 'L': d = (d + n.second / 90) % 4; break;
			case 'R': d = ((d + 4) - n.second / 90) % 4; break;
			case 'F':
			{
				switch (d)
				{
				case 0: y -= n.second; break;
				case 1: x -= n.second; break;
				case 2: y += n.second; break;
				case 3: x += n.second; break;
				default: break;
				}
			}
			default: break;
			}
		}

		return abs(x) + abs(y);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto nav = load(input);

		int x = 0;
		int y = 0;
		int wpx = 10;
		int wpy = -1;
		for (const auto& n : nav)
		{
			switch (n.first)
			{
			case 'N': wpy -= n.second; break;
			case 'S': wpy += n.second; break;
			case 'E': wpx += n.second; break;
			case 'W': wpx -= n.second; break;
			case 'L':
			{
				if (n.second == 90) { int t = wpx; wpx = wpy; wpy = -t; }
				if (n.second == 180) { wpx = -wpx; wpy = -wpy; }
				if (n.second == 270) { int t = wpx; wpx = -wpy; wpy = t; }
				break;
			}
			case 'R':
			{
				if (n.second == 90) { int t = wpx; wpx = -wpy; wpy = t; }
				if (n.second == 180) { wpx = -wpx; wpy = -wpy; }
				if (n.second == 270) { int t = wpx; wpx = wpy; wpy = -t; }
				break;
			}
			case 'F':
			{
				x += n.second * wpx;
				y += n.second * wpy;
				break;
			}
			default: break;
			}
		}

		return abs(x) + abs(y);
	}
}
