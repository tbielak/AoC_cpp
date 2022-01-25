#ifndef __2019_10__
#define __2019_10__

#include "../shared/Solution.h"

namespace Day10_2019
{
	class Position
	{
	public:
		Position();
		Position(int x, int y);

		bool operator < (const Position& other) const;
		bool operator != (const Position& other) const;
		bool operator == (const Position& other) const;

		int x;
		int y;
	};

	typedef map<Position, int> t_mapAsteroids;
	typedef pair<const Position, int> t_mapAsteroidsElement;

	class AngleDistance
	{
	public:
		AngleDistance(double angle, double distance);

		bool operator < (const AngleDistance& other) const;

		double angle;
		double distance;
	};

	typedef map<AngleDistance, Position> t_mapAsteroidsAngleDistance;

	class Space
	{
	public:
		Space(const vector<string>& input);

		t_mapAsteroidsElement best_location_asteroids();
		int laser_vaporization(const Position& best, int steps);

	private:
		int _width;
		int _height;
		t_mapAsteroids _asteroids;

		int isgn(int x);
		int gcd(int a, int b);
		
		void check_if_detectable(const Position& me, const Position& other, int& detected);
		AngleDistance find_angle_and_distance(const Position& laser, const Position& asteroid);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
