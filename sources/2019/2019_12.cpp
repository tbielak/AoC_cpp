#include "2019_12.h"

namespace Day12_2019
{
	Point3D::Point3D()
	:	x(0), y(0), z(0)
	{
	}

	Point3D::Point3D(int x, int y, int z)
	:	x(x), y(y), z(z)
	{
	}

	Point3D& Point3D::operator += (const Point3D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Point3D Point3D::operator - (const Point3D& v)
	{
		return Point3D(x - v.x, y - v.y, z - v.z);
	}

	int Point3D::energy() const
	{
		return iabs(x) + iabs(y) + iabs(z);
	}
	
	int Point3D::iabs(int v) const
	{
		return (v < 0) ? -v : v;
	}

	int isgn(int v)
	{
		if (v < 0) return -1;
		if (v > 0) return 1;
		return 0;
	}

	Point3D sgn3d(const Point3D& v)
	{
		return Point3D(isgn(v.x), isgn(v.y), isgn(v.z));
	}

	t_points Main::load(const vector<string>& input)
	{
		t_points points;
		regex regex("<x=([-]?[0-9]*), y=([-]?[0-9]*), z=([-]?[0-9]*)>");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			points.push_back(Point3D(stoi(matches[1].str()), stoi(matches[2].str()), stoi(matches[3].str())));
		}

		return points;
	}

	template<typename Type, typename Functor>
	void Main::one_step(vector<Type>& positions, vector<Type>& velocity, Functor signum) const
	{
		for (size_t i = 0; i < positions.size(); i++)
			for (size_t j = 0; j < positions.size(); j++)
				if (i != j)
					velocity[i] += signum(positions[j] - positions[i]);

		for (size_t i = 0; i < positions.size(); i++)
			positions[i] += velocity[i];
	}

	int Main::full_cycle(const vector<int>& input) const
	{
		int step = 0;
		vector<int> positions(input.size());
		vector<int> velocity(input.size());
		vector<int> zeroes = velocity;

		for (size_t i = 0; i < input.size(); i++)
			positions[i] = input[i];

		do
		{
			step++;
			one_step(positions, velocity, [](int v) -> int { return isgn(v); });
		} while (input != positions || velocity != zeroes);

		return step;
	}

	int64_t Main::gcd(int64_t a, int64_t b) const
	{
		int64_t tmp;
		while (b != 0)
		{
			tmp = b;
			b = a % b;
			a = tmp;
		}
		return a;
	}

	int64_t Main::gcm(int64_t a, int64_t b) const
	{
		return a / gcd(a, b) * b;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_points positions = load(input);

		vector<Point3D> velocity(positions.size());
		for (int t = 0; t < 1000; t++)
			one_step(positions, velocity, [](const Point3D& v) -> Point3D { return sgn3d(v); });

		int total_energy = 0;
		for (size_t i = 0; i < positions.size(); i++)
			total_energy += positions[i].energy() * velocity[i].energy();

		return total_energy;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_points positions = load(input);

		// pivot input
		vector<vector<int>> x(3);
		for (const auto& p : positions)
		{
			x[0].push_back(p.x);
			x[1].push_back(p.y);
			x[2].push_back(p.z);
		}

		// calculate result
		auto c1 = full_cycle(x[0]);
		auto c2 = full_cycle(x[1]);
		auto c3 = full_cycle(x[2]);
		return gcm(gcm(c1, c2), c3);
	}
}
