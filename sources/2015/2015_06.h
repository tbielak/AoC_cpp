#ifndef __2015_06__
#define __2015_06__

#include "../shared/input_output.h"

namespace Day06_2015
{
	typedef pair<int, int> t_point;
	enum class Command { turn_on, turn_off, toggle };

	class Instruction
	{
	public:
		Instruction(const string& s, const t_point& from, const t_point& to);

		Command cmd;
		t_point from;
		t_point to;
	};

	typedef vector<Instruction> t_vecInstruction;

	class Grid
	{
	public:
		Grid();

		void set(const t_point& from, const t_point& to, int v);
		void toggle(const t_point& from, const t_point& to);
		void add(const t_point& from, const t_point& to, int v);
		void dec(const t_point& from, const t_point& to);
		int sum();

	private:
		vector<vector<int>> _lights;
	};

	t_output main(const t_input& input);
}

#endif
