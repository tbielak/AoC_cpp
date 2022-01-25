#include "2021_21.h"

namespace Day21_2021
{
	Pair::Pair(int64_t p0 /* = 0 */, int64_t p1 /* = 0 */)
	{
		_v[0] = p0;
		_v[1] = p1;
	}

	int64_t& Pair::operator[] (int idx)
	{
		return _v[idx];
	}

	int64_t Pair::operator[] (int idx) const
	{
		return _v[idx];
	}

	bool Pair::operator < (const Pair& rhs) const
	{
		return (_v[0] == rhs._v[0]) ? _v[1] < rhs._v[1] : _v[0] < rhs._v[0];
	}

	Pair Main::load(const vector<string>& input)
	{
		// note: subtracting 1 from player position to ease modulo 10 operations
		return Pair(
			stoi(input[0].substr(input[0].find_first_of(':') + 1)) - 1,
			stoi(input[1].substr(input[1].find_first_of(':') + 1)) - 1
		);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		Pair position = load(input);

		// regular game, nothing fancy here :)
		Pair score;
		int current_player = 0;    // opponent = current_player ^ 1
		int dice_score = 0;        // dice score range: 0..99 to ease modulo operation
		int roll_count = 0;

		while (1)
		{
			int points = 0;
			for (int i = 0; i < 3; i++)	// three rolls
			{
				points += ++dice_score;
				dice_score %= 100;
				roll_count++;
			}

			position[current_player] = (position[current_player] + points) % 10;
			score[current_player] += position[current_player] + 1;

			if (score[current_player] >= 1000)
				return score[current_player ^ 1] * roll_count;

			current_player ^= 1;
		}
	}

	// <points, paths> pairs:
	// points: how many points you can earn in three dice rolls (3..9)
	// paths: how many paths lead to this result (3^3 = 27 paths in total)
	static const vector<Result> results = { {3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1} };

	// recursive universe split 
	Pair Main::split(t_cache& cache, int current_player, Pair position, Pair score /* = Pair() */)
	{
		// before making the move check if the other player won
		// return pair:
		// first - number of wins of 1st player (0 or 1 here)
		// second - number of wins of 2nd player (0 or 1 here)
		if (score[current_player ^ 1] >= 21)
			return Pair(current_player ^ 1, current_player);

		// now: recursively count 1st and 2nd player wins
		Pair wins;

		// try all paths
		for (const auto& r : results)
		{
			// update position and score (like in regular game, see part one)
			position[current_player] = (position[current_player] + r.points) % 10;
			score[current_player] += position[current_player] + 1;

			// get result from cache (if alredy seen such case before), or split
			Pair result;
			auto cache_key = make_tuple(current_player, position, score);
			auto it = cache.find(cache_key);
			if (it == cache.end())
			{
				// not found in cache: recursive split and store in cache
				result = split(cache, current_player ^ 1, position, score);
				cache[cache_key] = result;
			}
			else
				// result already available in cache
				result = it->second;

			// sum number of wins per player
			wins[0] += r.paths * result[0];
			wins[1] += r.paths * result[1];

			// revert position and score update for next path
			score[current_player] -= position[current_player] + 1;
			position[current_player] = (position[current_player] - r.points) % 10;
		}

		return wins;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		Pair position = load(input);

		t_cache cache;
		Pair wins = split(cache, 0, position);
		return max(wins[0], wins[1]);
	}
}
