#ifndef __2019_12__
#define __2019_12__

#include "../shared/input_output.h"

namespace Day12_2019
{
	class Point3D
	{
	public:
		Point3D();
		Point3D(int x, int y, int z);

		Point3D& operator += (const Point3D& rhs);
		Point3D operator - (const Point3D& v);

		int energy() const;

		int x;
		int y;
		int z;

	private:
		int iabs(int v) const;
	};

	t_output main(const t_input& input);
}

#endif
