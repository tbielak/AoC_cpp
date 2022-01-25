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

	int Main::first_fly(int finish, const t_vecReindeer& reindeers)
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

	int Main::second_fly(int finish, const t_vecReindeer& input)
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

	t_vecReindeer Main::load(const vector<string>& input)
	{
		t_vecReindeer reindeers;
		regex regex("(.*)( can fly )([0-9]*)( km/s for )([0-9]*)( second| seconds)(, but then must rest for )([0-9]*)( second| seconds)([.])");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			reindeers.push_back(Reindeer(stoi(matches[3].str()), stoi(matches[5].str()), stoi(matches[8].str())));
		}

		return reindeers;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return first_fly(2503, load(input));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return second_fly(2503, load(input));
	}
}
