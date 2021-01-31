#ifndef __2015_14__
#define __2015_14__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
