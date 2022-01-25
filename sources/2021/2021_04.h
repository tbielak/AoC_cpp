#ifndef __2021_04__
#define __2021_04__

#include "../shared/Solution.h"

namespace Day04_2021
{
	typedef vector<pair<int, bool>> t_row;	// 5 pairs: (number, marked)
	typedef vector<t_row> t_board;			// 5 rows of the board

	class Bingo
	{
	public:
		Bingo(const vector<string>& input);

		int play(bool first_board);

	private:
		void read_random(const vector<string>& input);
		void read_boards(const vector<string>& input);

		bool mark(t_board& board, int number);
		bool check_win(t_board& board, int row, int col);
		int sum_unmarked(const t_board& board);

		vector<int> _random;
		vector<t_board> _boards;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
