#ifndef __2023_22__
#define __2023_22__

#include "../shared/Solution.h"

namespace Day22_2023
{
	class Point3D
	{
	public:
		Point3D();
		Point3D(const string& s);
		
		int x, y, z;
	};

	int constexpr PLANE_YZ = 0;
	int constexpr PLANE_XZ = 1;
	int constexpr PLANE_XY = 2;
	int constexpr PLANE_UNDEFINED = -1;

	class Cell
	{
	public:
		Cell(int id = -1, int plane = PLANE_UNDEFINED);

		int id;
		int plane;
	};

	typedef vector<vector<vector<Cell>>> t_cuboid;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static int fall(t_cuboid& cuboid, const Point3D& size, int remove = INT_MIN);
	};
}

#endif
