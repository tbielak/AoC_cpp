#ifndef __2020_22__
#define __2020_22__

#include "../shared/Solution.h"

namespace Day22_2020
{
	typedef list<int> t_deck;
	typedef vector<t_deck> t_players_decks;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_players_decks load(const vector<string>& input);
		static size_t score(const t_deck& deck);
		size_t recursive_play(bool main_game, size_t winner, t_players_decks deck);
	};
}

#endif
