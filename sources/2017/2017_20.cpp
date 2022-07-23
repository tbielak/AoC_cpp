#include "2017_20.h"

namespace Day20_2017
{
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

	bool Point3D::operator < (const Point3D& rhs) const
	{
		if (x == rhs.x)
			return (y == rhs.y) ? z < rhs.z : y < rhs.y;

		return x < rhs.x;
	}
	
	Particle::Particle(const Point3D& position, const Point3D& velocity, const Point3D& acceleration)
	:	position(position), velocity(velocity), acceleration(acceleration)
	{
	}

	int Particle::Manhattan_distance() const
	{
		return iabs(position.x) + iabs(position.y) + iabs(position.z);
	}

	int Particle::iabs(int v) const
	{
		return (v < 0) ? -v : v;
	}

	t_vecParticle Main::load(const vector<string>& input)
	{
		t_vecParticle p;
		smatch matches;
		regex regex("p=<([ -]*[0-9]*),([ -]*[0-9]*),([ -]*[0-9]*)>, v=<([ -]*[0-9]*),([ -]*[0-9]*),([ -]*[0-9]*)>, a=<([ -]*[0-9]*),([ -]*[0-9]*),([ -]*[0-9]*)>");

		for (const auto& s : input)
		{
			regex_search(s, matches, regex);
			p.push_back(Particle(
				Point3D(stoi(matches[1]), stoi(matches[2]), stoi(matches[3])),
				Point3D(stoi(matches[4]), stoi(matches[5]), stoi(matches[6])),
				Point3D(stoi(matches[7]), stoi(matches[8]), stoi(matches[9]))));
		}

		return p;
	}

	void Main::step(t_vecParticle& particles)
	{
		for (Particle& p : particles)
		{
			p.velocity += p.acceleration;
			p.position += p.velocity;
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto particles = load(input);

		vector<int> closest = vector<int>(particles.size(), 0);
		vector<int> distance = closest;
		
		for (int i = 0; i < 1000; i++)
		{
			step(particles);

			for (size_t j = 0; j < particles.size(); j++)
				distance[j] = particles[j].Manhattan_distance();

			int min_dist = *min_element(distance.begin(), distance.end());

			for (size_t j = 0; j < distance.size(); j++)
				if (distance[j] == min_dist)
					closest[j]++;
		}

		int max_value = *max_element(closest.begin(), closest.end());
		for (size_t j = 0; j < closest.size(); j++)
			if (closest[j] == max_value)
				return j;

		return -1;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto particles = load(input);

		size_t rep = 0;
		while (1)
		{
			step(particles);
			
			set<Point3D> known, collisions;
			for (const auto& p : particles)
			{
				if (known.find(p.position) == known.end())
					known.insert(p.position);
				else
					collisions.insert(p.position);
			}

			t_vecParticle reduced;
			for (const auto& p : particles)
			{
				if (collisions.find(p.position) == collisions.end())
					reduced.push_back(p);
			}

			if (reduced.size() < particles.size())
			{
				rep = 0;
				particles = reduced;
			}
			else
			{
				if (++rep == 20)
					return reduced.size();
			}
		} 

		return -1;
	}
}
