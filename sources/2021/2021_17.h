#ifndef __2021_17__
#define __2021_17__

#include "../shared/Solution.h"

namespace Day17_2021
{
	class Simulation
	{
	public:
		Simulation(int tx_min, int tx_max, int ty_min, int ty_max);

		void init(int ivx, int ivy);
		int launch();

		int tx_min, tx_max;   // target x
		int ty_min, ty_max;   // target y
		int vx, vy;           // velocity
		int x, y;             // current position
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const string& input);
	};
}

#endif
