#ifndef __2020_17__
#define __2020_17__

#include "../shared/input_output.h"

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

	class Slice
	{
	public:
		t_mapCubes cubes;
		int max_x, max_y;
	};

	class PocketDimension
	{
	public:
		static Slice load(const vector<string>& input);

		PocketDimension(bool go4d, const Slice& slice);

		int run();

	private:
		bool _go4d;
		t_mapCubes _cubes;
		int _min_x, _max_x, _min_y, _max_y, _max_z, _max_w;
		t_vecPoint4D _neighbours;

		void generate_neighbours();
		void cycle();
		void insert(t_mapCubes& target, const Point4D& center);
		void inflate();
		int count() const;
	};

	t_output main(const t_input& input);
}

#endif
