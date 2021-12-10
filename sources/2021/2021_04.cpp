#include "2021_04.h"

namespace Day04_2021
{
	Bingo::Bingo(const t_input& input)
	{
		read_random(input);
		read_boards(input);
	}

	void Bingo::read_random(const t_input& input)
	{
		int number;
		stringstream ss(input[0]);
		while (ss >> number)
		{
			_random.push_back(number);
			ss.ignore(1);
		}
	}

	void Bingo::read_boards(const t_input& input)
	{
		size_t idx = 1;
		while (idx < input.size())
		{
			idx++;
			_boards.push_back(t_board());

			for (int row = 0; row < 5; row++)
			{
				_boards.back().push_back(t_row());
				const string& s = input[idx++];
				for (int col = 0; col < 5; col++)
					_boards.back().back().push_back(make_pair(stoi(s.substr(col * 3, 2)), false));
			}
		}
	}

	int Bingo::play(bool first_board)
	{
		vector<bool> won = vector<bool>(_boards.size(), false);
		size_t won_count = 0;

		for (int number : _random)
		{
			for (int b = 0; b < (int)_boards.size(); b++)
			{
				if (won[b])
					continue;

				if (mark(_boards[b], number))
				{
					won[b] = true;
					won_count++;
					if (first_board || won_count == _boards.size())
						return sum_unmarked(_boards[b]) * number;
				}
			}
		}

		return -1;
	}

	bool Bingo::mark(t_board& board, int number)
	{
		for (size_t row = 0; row < 5; row++)
			for (size_t col = 0; col < 5; col++)
				if (board[row][col].first == number)
				{
					board[row][col].second = true;
					return check_win(board, (int)row, (int)col);
				}

		return false;
	}

	bool Bingo::check_win(t_board& board, int row, int col)
	{
		size_t count = 0;
		for (size_t i = 0; i < 5; i++)
			if (board[row][i].second)
				count++;

		if (count == 5)
			return true;

		count = 0;
		for (size_t i = 0; i < 5; i++)
			if (board[i][col].second)
				count++;

		return count == 5;
	}

	int Bingo::sum_unmarked(const t_board& board)
	{
		int sum = 0;
		for (int row = 0; row < 5; row++)
			for (int col = 0; col < 5; col++)
				if (!board[row][col].second)
					sum += board[row][col].first;

		return sum;
	}
	
	int part_one(Bingo bingo)	// make board copy
	{
		return bingo.play(true);
	}

	int part_two(Bingo& bingo)	// use existing board (by reference)
	{
		return bingo.play(false);
	}

	t_output main(const t_input& input)
	{
		Bingo bingo(input);
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(bingo);
		auto p2 = part_two(bingo);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
