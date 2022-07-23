#ifndef __2017_20__
#define __2017_20__

#include "../shared/Solution.h"

namespace Day20_2017
{
	class Point3D
	{
	public:
		Point3D(int x, int y, int z);

		Point3D& operator += (const Point3D& rhs);
		bool operator < (const Point3D& rhs) const;

		int x, y, z;
	};

	class Particle
	{
	public:
		Particle(const Point3D& position, const Point3D& velocity, const Point3D& acceleration);
		int Manhattan_distance() const;

		Point3D position, velocity, acceleration;

	private:
		int iabs(int v) const;
	};

	typedef vector<Particle> t_vecParticle;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_vecParticle load(const vector<string>& input);
		static void step(t_vecParticle& particles);
	};
}

#endif
