#include "2019_10.h"

namespace Day10_2019
{
	Position::Position()
	:	x(0), y(0)
	{
	}

	Position::Position(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Position::operator < (const Position& other) const
	{
		return (y == other.y) ? x < other.x : y < other.y;
	}

	bool Position::operator != (const Position& other) const
	{
		return (x == other.x && y == other.y) ? false : true;
	}

	bool Position::operator == (const Position& other) const
	{
		return (x == other.x && y == other.y);
	}

	AngleDistance::AngleDistance(double angle, double distance)
	:	angle(angle), distance(distance)
	{
	}

	bool AngleDistance::operator < (const AngleDistance& other) const
	{
		return (angle == other.angle) ? distance < other.distance : angle < other.angle;
	}

	Space::Space(const vector<string>& input)
	{
		_width = (int)input[0].size();
		_height = (int)input.size();
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				if (input[y][x] == '#')
					_asteroids[Position(x, y)] = 0;
	}

	t_mapAsteroidsElement Space::best_location_asteroids()
	{
		// creating out map:
		//   first: position of monitoring station
		//   second: number of asteroids detected
		t_mapAsteroids out;
		int max_detected = int(_asteroids.size()) - 1;

		for (auto& me : _asteroids)
		{
			// assume we can detect all asteroids from the place
			auto station = out.insert(t_mapAsteroids::value_type(me.first, max_detected));
			auto detection_counter = station.first;

			// use _asteroids.second as visited flag
			for (auto& other : _asteroids)
				other.second = other == me;

			// check how many asteroids are detectable (decrease counter)
			for (auto& other : _asteroids)
				if (me != other)
					check_if_detectable(me.first, other.first, detection_counter->second);
		}

		// find best place
		auto best_it = out.begin();
		for (auto it = out.begin(); it != out.end(); it++)
			if (best_it->second < it->second)
				best_it = it;

		// return best location and number of asteroids
		return make_pair(best_it->first, best_it->second);
	}

	int Space::laser_vaporization(const Position& best, int steps)
	{
		// use _asteroids.second as vaporized flag
		// starting from best place
		for (auto& ast : _asteroids)
			ast.second = (ast.first == best) ? 1 : 0;

		int result = -1;
		double angle = -1;
		for (int i = 1; i <= steps; i++)
		{
			// map asteroid (angle, distance) to asteroid position
			t_mapAsteroidsAngleDistance map;
			for (const auto& ast : _asteroids)
				if (ast.second == 0)  // not vaporized yet?
					map[find_angle_and_distance(best, ast.first)] = ast.first;

			// find candidate to vaporize
			auto vi = map.begin();
			if (vi == map.end())
				break;

			while (vi != map.end() && vi->first.angle <= angle)
				vi++;

			if (vi == map.end())
				vi = map.begin();

			Position vap = vi->second;

			// vaporize it
			_asteroids.find(vap)->second = 1;

			// start next step from this angle
			angle = vi->first.angle;

			// calculate result
			if (i == steps)
				result = vap.x * 100 + vap.y;
		}

		return result;
	}

	int Space::isgn(int x)
	{
		return (x < 0) ? -1 : 1;
	}

	int Space::gcd(int a, int b)
	{
		if (a == 0 || b == 0)
			return 1;

		while (a != b)
			if (a < b) b -= a; else a -= b;

		return a;
	}

	void Space::check_if_detectable(const Position& me, const Position& other, int& detected)
	{
		// find moving vector (dx, dy)
		int x = other.x;
		int y = other.y;
		int dx = x - me.x;
		int dy = y - me.y;
		if (dx == 0) dy = isgn(dy);
		if (dy == 0) dx = isgn(dx);
		int n = gcd(abs(dx), abs(dy));
		dx /= n;
		dy /= n;

		// make step
		x += dx;
		y += dy;
		while (x >= 0 && x < _width && y >= 0 && y < _height)
		{
			// check if can find not visited asteroid at (x, y)
			const auto ast = _asteroids.find(Position(x, y));
			if (ast != _asteroids.end() && ast->second == 0)
			{
				// if so, location is blocked, cannot be detected
				detected--;
				ast->second = 1;
			}

			// make next step
			x += dx;
			y += dy;
		}
	}

	AngleDistance Space::find_angle_and_distance(const Position& laser, const Position& asteroid)
	{
		double dx = double(laser.x) - double(asteroid.x);
		double dy = double(laser.y) - double(asteroid.y);
		double distance = sqrt(dx * dx + dy * dy);

		double angle = 0.;
		if (laser.x - asteroid.x == 0)
			angle = (asteroid.y > laser.y) ? 180 : 0;
		else
		{
			constexpr double PI = 3.14159265358979323846;
			double fi = 360 / (2 * PI / fabs(atan(dy / dx)));

			if (asteroid.x > laser.x && asteroid.y <= laser.y)
				angle = 90 - fi;
			else
				if (asteroid.x > laser.x && asteroid.y > laser.y)
					angle = 90 + fi;
				else
					if (asteroid.x < laser.x && asteroid.y > laser.y)
						angle = 270 - fi;
					else
						angle = 270 + fi;
		}

		return AngleDistance(angle, distance);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Space(input).best_location_asteroids().second;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		Space space = Space(input);
		return space.laser_vaporization(space.best_location_asteroids().first, 200);
	}
}
