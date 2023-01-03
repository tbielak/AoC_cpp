#ifndef __2018_17__
#define __2018_17__

#include "../shared/Solution.h"

namespace Day17_2018
{
	class Simulation
	{
	public:
		Simulation(const vector<string>& input);
		void run();
		int count(const string& match) const;

	private:
		vector<string> _map;
		int _xstart, _ymin, _ymax;

		bool clay_or_rest_water(int x, int y) const;
		bool falling_water(int x, int y) const;
		bool spread(int& x, int y, int add);
		void spring(int x, int y);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);
	};
}

#endif
