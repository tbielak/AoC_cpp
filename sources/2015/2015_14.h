#ifndef __2015_14__
#define __2015_14__

#include "../shared/Solution.h"

namespace Day14_2015
{
	class Reindeer
	{
	public:
		Reindeer(int speed, int fly, int rest);

		int speed;
		int fly;
		int rest;
	};

	typedef vector<Reindeer> t_vecReindeer;

	class Race : public Reindeer
	{
	public:
		Race(const Reindeer& r);

		void tick();
		void award(int dist);

		bool is_flying;
		int secs_left;
		int current_speed;
		int distance;
		int awards;
	};

	typedef vector<Race> t_vecRace;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_vecReindeer load(const vector<string>& input);

		static int first_fly(int finish, const t_vecReindeer& reindeers);
		static int second_fly(int finish, const t_vecReindeer& input);
	};
}

#endif
