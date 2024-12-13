#include "2024_12.h"

namespace Day12_2024
{
	// fence bits
	static constexpr int RIGHT = 1 << 0;
	static constexpr int DOWN = 1 << 1;
	static constexpr int LEFT = 1 << 2;
	static constexpr int UP = 1 << 3;
	static constexpr int ALL = RIGHT + DOWN + LEFT + UP;
	static vector<int> clear_mask = { ALL - RIGHT, ALL - DOWN, ALL - LEFT, ALL - UP };

	// move: 0 = right, 1 = down, 2 = left, 3 = up
	static vector<int> move_x = { 1, 0, -1, 0 };
	static vector<int> move_y = { 0, 1, 0, -1 };

	Farm::Farm(const vector<string>& input)
	:	_input(input)
	{
		_height = (int)input.size();
		_width = (int)input[0].size();

		_fence = vector<vector<int>>(_height, vector<int>(_width, ALL));
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				for (int i = 0; i < 4; i++)
				{
					int nx = x + move_x[i];
					int ny = y + move_y[i];
					if (nx < 0 || nx >= _width || ny < 0 || ny >= _height)
						continue;

					if (input[y][x] == input[ny][nx])
					{
						_fence[y][x] &= clear_mask[i];
						_fence[ny][nx] &= clear_mask[i ^ 2];
					}
				}
	}

	int Farm::price(bool with_discount)
	{
		return price(with_discount ? fence_reduced() : _fence);
	}

	vector<vector<int>> Farm::fence_reduced()
	{
		auto reduced = _fence;
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				for (int i = 0; i < 4; i++)
					if (_fence[y][x] & (1 << i))
					{
						int nx = x + (i & 1);
						int ny = y + ((i & 1) ^ 1);

						while (nx < _width && ny < _height && _input[ny][nx] == _input[y][x] && _fence[ny][nx] & (1 << i))
						{
							reduced[ny][nx] &= clear_mask[i];
							nx += (i & 1);
							ny += ((i & 1) ^ 1);
						}
					}

		return reduced;
	}

	int Farm::bit_count(int v) const
	{
		int b = 0;
		if (v & 1) b++;
		if (v & 2) b++;
		if (v & 4) b++;
		if (v & 8) b++;
		return b;
	}

	int Farm::price(const vector<vector<int>>& fence_to_be_valued)
	{
		vector<vector<bool>> visited = vector<vector<bool>>(_height, vector<bool>(_width, false));
		int sum = 0;
		while (1)
		{
			int nx = -1;
			int ny = -1;
			for (int y = 0; y < _height; y++)
			{
				for (int x = 0; x < _width; x++)
					if (!visited[y][x])
					{
						nx = x;
						ny = y;
						break;
					}

				if (nx != -1)
					break;
			}

			if (nx == -1)
				break;

			int c = 0;
			int f = 0;
			queue<pair<int, int>> q;
			q.push(make_pair(nx, ny));
			while (q.size())
			{
				auto [x, y] = q.front();
				q.pop();

				if (visited[y][x])
					continue;

				c++;
				f += bit_count(fence_to_be_valued[y][x]);
				visited[y][x] = true;

				for (int i = 0; i < 4; i++)
					if ((_fence[y][x] & (1 << i)) == 0)
						q.push(make_pair(move_x[i] + x, move_y[i] + y));
			}

			sum += f * c;
		}

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Farm(input).price(false);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Farm(input).price(true);
	}
}
