#include "2022_09.h"

namespace Day09_2022
{
	t_point Main::move_tail(int hx, int hy, int tx, int ty)
	{
		static vector<int> dx = { -1, -1, 0, 1, 1, -1, 0, 0, 0, 1, -1, 0, 0, 0, 1, -1, 0, 0, 0, 1, -1, -1, 0, 1, 1 };
		static vector<int> dy = { -1, -1, -1, -1, -1, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 };

		int idx = (hx - tx + 2) + (hy - ty + 2) * 5;
		return make_pair(tx + dx[idx], ty + dy[idx]);
	}

	size_t Main::move_snake(const vector<string>& input, int parts)
	{
		vector<t_point> snake = vector<t_point>(parts, make_pair(0, 0));
		t_visited visited;
		visited.insert(snake.back());
		for (const auto& s : input)
		{
			char direction = s[0];
			int steps = stoi(s.substr(2));
			for (int i = 0; i < steps; i++)
			{
				if (direction == 'L') snake[0].first--;
				if (direction == 'R') snake[0].first++;
				if (direction == 'U') snake[0].second--;
				if (direction == 'D') snake[0].second++;
				for (int i = 1; i < (int)snake.size(); i++)
					snake[i] = move_tail(snake[i - 1].first, snake[i - 1].second, snake[i].first, snake[i].second);

				visited.insert(snake.back());
			}
		}

		return visited.size();
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return move_snake(input, 2);
	}
		
	AoC::Output Main::part_two(const vector<string>& input)
	{
		return move_snake(input, 10);
	}
}
