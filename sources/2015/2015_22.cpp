#include "2015_22.h"

namespace Day22_2015
{
	State::State()
	:	player_hitpoints(-1), player_mana(-1), player_mana_spent(-1), boss_hitpoints(-1), boss_damage(-1)
	{
	}

	State::State(int player_hitpoints, int player_mana, int player_mana_spent, int boss_hitpoints, int boss_damage)
	:	player_hitpoints(player_hitpoints), player_mana(player_mana), player_mana_spent(player_mana_spent),
		boss_hitpoints(boss_hitpoints), boss_damage(boss_damage)
	{
		spell_timers = vector<int>(spell_count);
	}

	Game::Game(bool hard_level, int boss_hitpoints, int boss_damage)
	:	_hard_level(hard_level), _least_mana_spent(INT_MAX)
	{
		_init = State(50, 500, 0, boss_hitpoints, boss_damage);
	}

	int Game::run()
	{
		for (int sp = 0; sp < spell_count; sp++)
			go(_init, sp, -1);

		return _least_mana_spent;
	}

	void Game::go(State state, int spell, int idx)
	{
		if (_hard_level)
		{
			state.player_hitpoints--;
			if (state.player_hitpoints <= 0)
				return;  // player looses here
		}

		// --- Player turn
		apply_effects(state);

		if (state.boss_hitpoints <= 0)
		{
			_least_mana_spent = min(_least_mana_spent, state.player_mana_spent);
			return;  // player wins here
		}

		if (state.spell_timers[spell] > 0)
			return;  // spell blocked

		if (state.player_mana < _spell_cost[spell])
			return;  // no way, no mana to cast a spell

		// money transfer
		state.player_mana -= _spell_cost[spell];
		state.player_mana_spent += _spell_cost[spell];

		if (state.player_mana_spent > _least_mana_spent)
			return;  // already too expensive to continue

		// now.. some magic!
		switch (spell)
		{
			case Magic_Missile: { state.boss_hitpoints -= 4; break; }
			case Drain: { state.boss_hitpoints -= 2; state.player_hitpoints += 2; break; }
			case Shield: { state.spell_timers[Shield] = 6; break; }
			case Poison: { state.spell_timers[Poison] = 6; break; }
			case Recharge: { state.spell_timers[Recharge] = 5; break; }
			default: break;
		}

		// --- Boss turn
		int armor = apply_effects(state);

		if (state.boss_hitpoints <= 0)
		{
			_least_mana_spent = min(_least_mana_spent, state.player_mana_spent);
			return;  // player wins here
		}

		// boss hits
		int damage = state.boss_damage - armor;
		if (damage < 1) damage = 1;
		state.player_hitpoints -= damage;
		if (state.player_hitpoints <= 0)
			return;  // player looses here

		// try (recursively) another spell from current state
		if (idx > -1)
		{
			idx++;
			go(state, idx, idx);
		}
		else
		{
			for (int sp = 0; sp < spell_count; sp++)
				go(state, sp, -1);
		}
	}

	int Game::apply_effects(State& state)
	{
		int armor = 0;
		if (state.spell_timers[Shield] > 0)
		{
			state.spell_timers[Shield]--;
			if (state.spell_timers[Shield] > 0)
				armor = 7;
		}

		if (state.spell_timers[Poison] > 0)
		{
			state.spell_timers[Poison]--;
			state.boss_hitpoints -= 3;
		}

		if (state.spell_timers[Recharge] > 0)
		{
			state.spell_timers[Recharge]--;
			state.player_mana += 101;
		}

		return armor;
	}

	int part_one(int boss_hitpoints, int boss_damage)
	{
		Game game(false, boss_hitpoints, boss_damage);
		return game.run();
	}

	int part_two(int boss_hitpoints, int boss_damage)
	{
		Game game(true, boss_hitpoints, boss_damage);
		return game.run();
	}

	t_output main(const t_input& input)
	{
		int boss_hitpoints = stoi(input[0].substr(input[0].find(": ") + 2));
		int boss_damage = stoi(input[1].substr(input[1].find(": ") + 2));
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(boss_hitpoints, boss_damage);
		auto p2 = part_two(boss_hitpoints, boss_damage);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
