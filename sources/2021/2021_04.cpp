#include "2021_04.h"

namespace Day04_2021
{
	Bingo::Bingo(const vector<string>& input)
	{
		read_random(input);
		read_boards(input);
	}

	void Bingo::read_random(const vector<string>& input)
	{
		int number;
		stringstream ss(input[0]);
		while (ss >> number)
		{
			_random.push_back(number);
			ss.ignore(1);
		}
	}

	void Bingo::read_boards(const vector<string>& input)
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
	
	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Bingo(input).play(true);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Bingo(input).play(false);
	}
}
