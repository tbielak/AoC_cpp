#ifndef __2018_18__
#define __2018_18__

#include "../shared/Solution.h"

namespace Day18_2018
{
	class LumberCollection
	{
	public:
		LumberCollection(const vector<string>& input);

		int run(int minutes);

	private:
		vector<string> _area;
		int _width;
		int _height;

		int adjacent(int x, int y, char match) const;
		int count(char match) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
