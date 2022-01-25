#include "2021_17.h"

namespace Day17_2021
{
	Simulation::Simulation(int tx_min, int tx_max, int ty_min, int ty_max)
	:	tx_min(tx_min), tx_max(tx_max), ty_min(ty_min), ty_max(ty_max),
		vx(), vy(0), x(0), y(0)
	{
	}

	void Simulation::init(int ivx, int ivy)
	{
		vx = ivx;
		vy = ivy;
		x = 0;
		y = 0;
	}

	int Simulation::launch()
	{
		int y_max = 0;
		while (1)
		{
			x += vx;
			y += vy;
			y_max = max(y_max, y);

			if (vx > 0) vx--;
			vy--;

			if (x > tx_max || y < ty_min)
				return INT_MIN;	// miss

			if (x >= tx_min && x <= tx_max && y >= ty_min && y <= ty_max)
				return y_max;
		}
	}

	AoC::Output Main::both_parts(const string& input)
	{
		smatch matches;
		regex regex("target area: x=([-|0-9]*)..([-|0-9]*), y=([-|0-9]*)..([-|0-9]*)");
		regex_search(input, matches, regex);
		Simulation sim(stoi(matches[1]), stoi(matches[2]), stoi(matches[3]), stoi(matches[4]));

		int y_max_found = INT_MIN;
		int count = 0;

		for (int vy = sim.tx_max; vy >= -sim.tx_max; vy--)
			for (int vx = sim.tx_max; vx >= 0; vx--)
			{
				sim.init(vx, vy);
				int y_max = sim.launch();
				if (y_max > INT_MIN)
				{
					count++;
					if (y_max_found == INT_MIN)
						y_max_found = y_max;
				}
			}

		return make_pair(y_max_found, count);
	}
}
