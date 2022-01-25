#include "2020_22.h"

namespace Day22_2020
{
	t_players_decks Main::load(const vector<string>& input)
	{
		t_players_decks deck(2);
		size_t idx = 1;
		for (int i = 0; i < 2; i++)
		{
			for (; idx < input.size(); idx++)
			{
				if (input[idx] == "")
					break;

				deck[i].push_back(stoi(input[idx]));
			}

			idx += 2;
		}

		return deck;
	}

	size_t Main::score(const t_deck& deck)
	{
		size_t v = 0;
		size_t i = deck.size();
		for (const auto& card : deck)
			v += i-- * card;

		return v;
	}

	size_t Main::recursive_play(bool main_game, size_t winner, t_players_decks deck)
	{
		vector<int> card(2);
		set<pair<size_t, size_t>> state;

		while (1)
		{
			pair<size_t, size_t> s = { score(deck[0]), score(deck[1]) };
			if (state.find(s) != state.end())
				return 0;

			state.insert(s);

			card[0] = deck[0].front();
			card[1] = deck[1].front();
			deck[0].pop_front();
			deck[1].pop_front();

			winner = card[0] < card[1];
			if ((int)deck[0].size() >= card[0] && (int)deck[1].size() >= card[1])
			{
				t_players_decks subgame = deck;
				subgame[0].resize(card[0]);
				subgame[1].resize(card[1]);
				winner = recursive_play(false, winner, subgame);
			}

			deck[winner].push_back(card[winner]);
			deck[winner].push_back(card[winner ^ 1]);
			if (deck[winner ^ 1].empty())
			{
				if (main_game)
					return score(deck[winner]);

				return winner;
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>&input)
	{
		auto deck = load(input);

		size_t winner = 0;
		vector<int> card(2);
		while (!deck[winner ^ 1].empty())
		{
			card[0] = deck[0].front();
			card[1] = deck[1].front();
			deck[0].pop_front();
			deck[1].pop_front();

			winner = card[0] < card[1];
			deck[winner].push_back(card[winner]);
			deck[winner].push_back(card[winner ^ 1]);
		}

		return score(deck[winner]);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return recursive_play(true, 0, load(input));
	}
}
