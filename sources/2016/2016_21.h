#ifndef __2016_21__
#define __2016_21__

#include "../shared/Solution.h"

namespace Day21_2016
{
	enum class Command
	{
		swap_position,
		swap_letter,
		rotate_left,
		rotate_right,
		rotate_based,
		reverse_positions,
		move_position
	};

	class Operation
	{
	public:
		Operation(enum Command cmd, int x, int y);
		Operation(enum Command cmd, char cx, char cy);

		enum Command cmd;
		int x, y;
		char cx, cy;
	};

	typedef vector<Operation> t_operations;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static string get_word(string& s, int skip = 0);
		static t_operations load(const vector<string>& input);
		static string scramble(string password, const t_operations& operations);
	};
}

#endif
