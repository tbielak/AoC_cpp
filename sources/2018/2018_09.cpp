#include "2018_09.h"

namespace Day09_2018
{
	Marble::Marble(int number)
	:	number(number), prev(0), next(0)
	{
	}

	int64_t Main::solve(int players, int last_marble)
	{
		Marble* current = new Marble(0);
		current->prev = current;
		current->next = current;

		vector<int64_t> score = vector<int64_t>(players);

		for (int i = 1; i <= last_marble; i++)
		{
			if ((i % 23) > 0)
			{
				Marble* p = current->next;
				Marble* q = p->next;
				current = new Marble(i);
				p->next = current;
				current->next = q;
				q->prev = current;
				current->prev = p;
			}
			else
			{
				for (int j = 0; j < 7; j++)
					current = current->prev;

				score[(i - 1) % players] += current->number + i;

				Marble* p = current->prev;
				Marble* q = current->next;
				p->next = q;
				q->prev = p;
				delete current;
				current = q;
			}
		}

		int64_t winning_score = *max_element(score.begin(), score.end());
		
		// --> deallocate the ring (not crucial for the solution)
		Marble* p = current;
		while (p->next != current)
		{
			Marble* q = p;
			p = p->next;
			delete q;
		}
		// <--

		return winning_score;
	}

	pair<int, int> Main::load(const string& input)
	{
		smatch matches;
		regex regex("([0-9]+) players; last marble is worth ([0-9]+) points");
		regex_search(input, matches, regex);
		return make_pair(stoi(matches[1]), stoi(matches[2]));
	}

	AoC::Output Main::part_one(const string& input)
	{
		auto [players, last_marble] = load(input);
		return solve(players, last_marble);
	}

	AoC::Output Main::part_two(const string& input)
	{
		auto [players, last_marble] = load(input);
		return solve(players, last_marble * 100);
	}
}
