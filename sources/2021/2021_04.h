#ifndef __2021_04__
#define __2021_04__

#include "../shared/input_output.h"

namespace Day04_2021
{
	t_output main(const t_input& input);

	typedef vector<pair<int, bool>> t_row;	// 5 pairs: (number, marked)
	typedef vector<t_row> t_board;			// 5 rows of the board

	class Bingo
	{
	public:
		Bingo(const t_input& input);

		int play(bool first_board);

	private:
		void read_random(const t_input& input);
		void read_boards(const t_input& input);

		bool mark(t_board& board, int number);
		bool check_win(t_board& board, int row, int col);
		int sum_unmarked(const t_board& board);

		vector<int> _random;
		vector<t_board> _boards;
	};
}

#endif
