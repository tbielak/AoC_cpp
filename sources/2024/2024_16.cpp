#include "2024_16.h"

namespace Day16_2024
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// flatten maze!
		string maze;
		for (const auto& s : input)
			maze += s;

		// update position when going { North, East, South, West }
		int width = (int)input[0].size();
		const vector<int> moves = { -width, 1, width, -1 };

		// start and end point
		int start = (int)maze.find_first_of("S");
		int end = (int)maze.find_first_of("E");

		// map (position * 4 + direction) to score
		map<int, int> known_scores;

		// lowest score = solution of part one
		int lowest_score = INT_MAX;

		// all paths found coded as sequence of moves: S=step, L=turn left, R=turn right
		vector<string> all_paths;

		// state: score, position, direction, path
		typedef tuple<int, int, int, string> t_state;

		// Dikstra algorithm: priority queue ordered primarily by score
		priority_queue<t_state, vector<t_state>, greater<t_state>> pq;

		// initial state (1 = East)
		pq.push(make_tuple(0, start, 1, string()));

		while (!pq.empty())
		{
			// get element from priority queue (with lowest score)
			auto [score, position, direction, path] = pq.top();
			pq.pop();

			// already found all lowest score paths, quit
			if (score > lowest_score)
				break;

			// check if score already known and lowest
			auto key = position * 4 + direction;
			if (known_scores.find(key) != known_scores.end() && known_scores[key] < score)
				continue;

			// add or update score
			known_scores[key] = score;

			// if end reached store lowest score and store the path leading to end
			if (position == end)
			{
				lowest_score = score;
				all_paths.push_back(path);
			}

			// go forward if there is no wall
			if (maze[position + moves[direction]] != '#')
				pq.push(make_tuple(score + 1, position + moves[direction], direction, path + "G"));

			// turn left and right
			pq.push(make_tuple(score + 1000, position, (direction + 3) % 4, path + "L"));
			pq.push(make_tuple(score + 1000, position, (direction + 1) % 4, path + "R"));
		}

		// part two, find all points on the paths
		set<int> points;
		points.insert(start);

		// go through all paths
		for (const auto& path : all_paths)
		{
			// starting position and direction (1 = East)
			int position = start;
			int direction = 1;

			// steps on path
			for (char step : path)
				if (step == 'L')
					direction = (direction + 3) % 4;
				else
				if (step == 'R')
					direction = (direction + 1) % 4;
				else
				{
					position += moves[direction];
					points.insert(position);
				}
		}

		// result: lowest score and number of points on the paths
		return make_pair(lowest_score, (int)points.size());
	}
}
