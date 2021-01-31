#include "2015_14.h"

namespace Day14_2015
{
	Reindeer::Reindeer(int speed, int fly, int rest)
	:	speed(speed), fly(fly), rest(rest)
	{
	}

	Race::Race(const Reindeer& r)
	:	Reindeer(r.speed, r.fly, r.rest),
		is_flying(true), secs_left(r.fly), current_speed(r.speed), distance(0), awards(0)
	{
	}

	void Race::tick()
	{
		distance += current_speed;
		secs_left--;
		if (secs_left == 0)
		{
			is_flying = !is_flying;
			secs_left = (is_flying) ? fly : rest;
			current_speed = (is_flying) ? speed : 0;
		}
	}

	void Race::award(int dist)
	{
		if (distance == dist)
			awards++;
	}

	int part_one(int finish, const t_vecReindeer& reindeers)
	{
		vector<int> distance(reindeers.size());
		for (size_t i = 0; i < reindeers.size(); i++)
		{
			int t = finish;
			int secs = 0;
			bool fly = true;
			while (t > 0)
			{
				secs = fly ? reindeers[i].fly : reindeers[i].rest;
				if (t < secs)
					secs = t;

				if (fly)
					distance[i] += secs * reindeers[i].speed;

				t -= secs;
				fly = !fly;
			}
		}

		return *max_element(distance.begin(), distance.end());
	}

	int part_two(int finish, const t_vecReindeer& input)
	{
		t_vecRace reindeers;
		for (const auto& i : input)
			reindeers.push_back(Race(i));

		for (int t = 0; t < finish; t++)
		{
			for (auto& r : reindeers)
				r.tick();

			int dmax = 0;
			for (const auto& r : reindeers)
				dmax = max(r.distance, dmax);

			for (auto& r : reindeers)
				r.award(dmax);
		}

		int amax = 0;
		for (const auto& r : reindeers)
			amax = max(r.awards, amax);

		return amax;
	}

	t_output main(const t_input& input)
	{
		t_vecReindeer vinput;
		regex regex("(.*)( can fly )([0-9]*)( km/s for )([0-9]*)( second| seconds)(, but then must rest for )([0-9]*)( second| seconds)([.])");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			vinput.push_back(Reindeer(stoi(matches[3].str()), stoi(matches[5].str()), stoi(matches[8].str())));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(2503, vinput);
		auto p2 = part_two(2503, vinput);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
