#include "2015_21.h"

namespace Day21_2015
{
	template<typename Functor>
	int Main::calculate(int rcfg, Functor ftor)
	{
		int c = 0;
		for (const auto& ring : rings)
		{
			if (rcfg & 1)
				c += ftor(ring);

			rcfg >>= 1;
		}

		return c;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		int boss_hitpoints = stoi(input[0].substr(input[0].find(": ") + 2));
		int boss_damage = stoi(input[1].substr(input[1].find(": ") + 2));
		int boss_armor = stoi(input[2].substr(input[2].find(": ") + 2));

		auto ring_damage = [](const Item& r) -> int { return r.damage; };
		auto ring_armor = [](const Item& r) -> int { return r.armor; };
		auto ring_cost = [](const Item& r) -> int { return r.cost; };
		auto bit_count = [](const Item& r) -> int { (void)(r); return 1; };

		int mincost = INT_MAX;
		int maxcost = -1;
		vector<int> player_hitpoints(2);
		vector<int> player_damage(2);
		vector<int> player_armor(2);

		int rcnt = 1 << (int)rings.size();
		for (int part = 1; part <= 2; part++)
			for (const auto& weapon : weapons)
				for (const auto& armor : armors)
					for (int rcfg = 0; rcfg < rcnt; rcfg++)
						if (calculate(rcfg, bit_count) <= 2)
						{
							// player (you)
							player_hitpoints[0] = 100;
							player_damage[0] = weapon.damage + armor.damage + calculate(rcfg, ring_damage);
							player_armor[0] = weapon.armor + armor.armor + calculate(rcfg, ring_armor);
							int cost = weapon.cost + armor.cost + calculate(rcfg, ring_cost);

							// boss (enemy)
							player_hitpoints[1] = boss_hitpoints;
							player_damage[1] = boss_damage;
							player_armor[1] = boss_armor;

							int cp = 0; // current player
							while (1)
							{
								// turn
								player_hitpoints[cp ^ 1] -= (player_damage[cp] - player_armor[cp ^ 1]);

								// loss?
								if (player_hitpoints[cp ^ 1] <= 0)
								{
									if (cp == 0 && part == 1)
										mincost = min(mincost, cost);

									if (cp == 1 && part == 2)
										maxcost = max(maxcost, cost);

									break;
								}

								// next player
								cp ^= 1;
							}
						}

		return pair<int, int>(mincost, maxcost);
	}
}
