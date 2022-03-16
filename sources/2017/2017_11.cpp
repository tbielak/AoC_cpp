#include "2017_11.h"

namespace Day11_2017
{
	// See https://www.redblobgames.com/grids/hexagons/  <-- it helped a lot!

	int Main::iabs(int v)
	{
		return (v < 0) ? -v : v;
	}

	int Main::distance(int x, int y)
	{
		return max(max(iabs(x), iabs(y)), iabs(x + y));
	}

	AoC::Output Main::both_parts(const string& input)
	{
		static map<string, pair<int, int>> moves_map = {
			{"n", {0, -1} }, {"ne", {1, -1} }, {"se", {1, 0} },
			{"s", {0, 1} }, {"sw", {-1, 1} }, {"nw", {-1, 0} }
		};

		int x = 0;
		int y = 0;
		int max_distance = 0;

		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
		{
			auto [mx, my] = moves_map.find(s)->second;
			x += mx;
			y += my;

			max_distance = max(max_distance, distance(x, y));
		}

		return make_pair(distance(x, y), max_distance);
	}
}
