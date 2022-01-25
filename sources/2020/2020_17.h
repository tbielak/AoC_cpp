#ifndef __2020_17__
#define __2020_17__

#include "../shared/Solution.h"

namespace Day17_2020
{
	class Point4D
	{
	public:
		Point4D(int x, int y, int z, int w);

		friend Point4D operator+ (Point4D lhs, const Point4D& rhs);
		bool operator < (const Point4D& rhs) const;
		const Point4D& symetrical();

		int x, y, z, w;
	};

	typedef vector<Point4D> t_vecPoint4D;
	typedef map<Point4D, bool> t_mapCubes;

	class PocketDimension
	{
	public:
		PocketDimension(bool go4d, const vector<string>& input);

		int run();

	private:
		bool _go4d;
		t_mapCubes _cubes;
		int _min_x, _max_x, _min_y, _max_y, _max_z, _max_w;
		t_vecPoint4D _neighbours;

		void cycle();
		void insert(t_mapCubes& target, const Point4D& center);
		void inflate();
		int count() const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
