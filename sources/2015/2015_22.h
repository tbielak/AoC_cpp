#ifndef __2015_22__
#define __2015_22__

#include "../shared/Solution.h"

namespace Day22_2015
{
	const int Magic_Missile = 0;
	const int Drain = 1;
	const int Shield = 2;
	const int Poison = 3;
	const int Recharge = 4;

	const int spell_count = 5;

	class State
	{
	public:
		State();
		State(int player_hitpoints, int player_mana, int player_mana_spent, int boss_hitpoints, int boss_damage);

		int player_hitpoints;
		int player_mana;
		int player_mana_spent;
		int boss_hitpoints;
		int boss_damage;
		vector<int> spell_timers;
	};

	class Game
	{
	public:
		Game(bool hard_level, const vector<string>& input);

		int run();

	private:
		bool _hard_level;
		State _init;
		int _least_mana_spent;
		const vector<int> _spell_cost = { 53, 73, 113, 173, 229 };

		void go(State state, int spell, int idx);
		int apply_effects(State& state);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
