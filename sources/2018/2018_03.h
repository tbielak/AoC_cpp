#ifndef __2018_03__
#define __2018_03__

#include "../shared/Solution.h"

namespace Day03_2018
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	class Fabric
	{
	public:
		Fabric();
		Fabric(const Point& point, int width, int height);

		Point point;
		int width;
		int height;
	};

	typedef map<int, Fabric> t_fabrics;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_fabrics load(const vector<string>& input);
	};
}

#endif
