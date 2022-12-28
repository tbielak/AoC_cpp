#include "2022_22.h"

namespace Day22_2022
{
	tuple<int, int, int> Main::control_cube_edges(int x, int y, int facing)
	{
		switch (facing)
		{
			case 0: // right
			{
				if (x == 50 && y >= 150)
					return make_tuple(y - 100, 149, 3);

				if (x == 100)
				{
					if (y >= 50 && y < 100)
						return make_tuple(y + 50, 49, 3);

					if (y >= 100)
						return make_tuple(149, 149 - y, 2);
				}

				if (x == 150)
					return make_tuple(99, 149 - y, 2);

				break;
			}

			case 1: // down
			{
				if (y == 50 && x >= 100)
					return make_tuple(99, x - 50, 2);

				if (y == 150 && x >= 50)
					return make_tuple(49, x + 100, 2);

				if (y == 200)
					return make_tuple(x + 100, 0, 1);

				break;
			}

			case 2: // left
			{
				if (x == -1)
				{
					if (y < 150)
						return make_tuple(50, 149 - y, 0);

					return make_tuple(y - 100, 0, 1);
				}

				if (x == 49)
				{
					if (y < 50)
						return make_tuple(0, 149 - y, 0);

					if (y < 100)
						return make_tuple(y - 50, 100, 1);
				}

				break;
			}

			default: // up
			{
				if (y == -1)
				{
					if (x < 100)
						return make_tuple(0, x + 100, 0);

					return make_tuple(x - 100, 199, 3);
				}

				if (y == 99 && x < 50)
					return make_tuple(50, x + 50, 0);

				break;
			}
		}

		return make_tuple(x, y, facing);
	}

	// Note: This solution solves only one shape of cube mesh (part two):
	//   [][]
	//   []
	// [][]
	// []
	// code below checks if the code is able to solve it, if not -1 would
	// be returned from Main::solve()
	//
	bool Main::solvable(const vector<string>& board)
	{
		return board.size() == 200 && board[0].size() == 150 &&
			board[0][0] == ' ' && board[0][50] != ' ' && board[0][100] != ' ' &&
			board[50][0] == ' ' && board[50][50] != ' ' && board[50][100] == ' ' &&
			board[100][0] != ' ' && board[100][50] != ' ' && board[100][100] == ' ' &&
			board[150][0] != ' ' && board[150][50] == ' ' && board[150][100] == ' ';
	}

	int Main::solve(const vector<string>& input, bool flat)
	{
		// load board and path
		vector<string> board = input;
		string path = input.back();
		board.pop_back();
		board.pop_back();

		int height = (int)board.size();
		int width = 0;
		for (auto& s : board)
			width = max(width, (int)s.size());

		for (auto& s : board)
			while ((int)s.size() < width) s += ' ';

		if (!flat && !solvable(board))
			return -1;	// cannot solve, sorry!

		// find starting position
		int x = 0;
		int y = 0;
		while (board[y][x] == ' ') x++;
		int facing = 0;
	
		// follow the path
		for (size_t p = 0; p < path.size(); p++)
		{
			// rotate
			if (path[p] > '9')
			{
				facing = (facing + (path[p] == 'R' ? 1 : -1)) & 3;
				continue;
			}

			// find number of steps
			string s;
			while (p < path.size() && path[p] <= '9')
				s += path[p++];
			int steps = stoi(s);
			p--;

			// walk
			for (int i = 0; i < steps; i++)
			{
				static vector<int> move_x = { 1, 0, -1, 0 };
				static vector<int> move_y = { 0, 1, 0, -1 };

				if (flat)
				{
					// flat grid = simple edge wrapping
					int nx = x + move_x[facing];
					int ny = y + move_y[facing];
					while (1)
					{
						if (nx == -1) nx = width - 1;
						if (nx == width) nx = 0;
						if (ny == -1) ny = height - 1;
						if (ny == height) ny = 0;

						if (board[ny][nx] != ' ')
							break;

						nx += move_x[facing];
						ny += move_y[facing];
					}

					if (board[ny][nx] == '#')
						break;

					x = nx;
					y = ny;
				}
				else
				{
					// cube mesh = more complicated case
					auto [nx, ny, nfacing] = control_cube_edges(x + move_x[facing], y + move_y[facing], facing);

					if (board[ny][nx] == '#')
						break;

					x = nx;
					y = ny;
					facing = nfacing;
				}
			}
		}

		return 1000 * (y + 1) + 4 * (x + 1) + facing;
	}


	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, true);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, false);
	}
}
