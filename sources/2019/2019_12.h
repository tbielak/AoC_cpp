#ifndef __2019_12__
#define __2019_12__

#include "../shared/Solution.h"

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

	typedef vector<Point3D> t_points;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_points load(const vector<string>& input);

		template<typename Type, typename Functor> void one_step(vector<Type>& positions, vector<Type>& velocity, Functor signum) const;
		int full_cycle(const vector<int>& input) const;
		int64_t gcd(int64_t a, int64_t b) const;
		int64_t gcm(int64_t a, int64_t b) const;
	};
}

#endif
