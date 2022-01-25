#include "2020_18_LALR.h"

namespace Day18_2020_LALR
{
	// PART ONE: LR(0)-class grammar:
	//
	//  R0: A' -> A terminator
	//  R1: A -> B
	//  R2: | A * B
	//  R3: | A + B
	//  R4: B -> number
	//  R5: | ( A )
	//
	//  non-terminals: A, B
	//  terminals: * + number ( ) terminator

	static t_vecint P1_suffix_length_array = { 2, 1, 3, 3, 1, 3 };
	static t_vecint P1_prefix_symbol_array = { -1, 0, 0, 0, 1, 1 };

	static t_vec2int P1_non_terminal_shift_array = {
		{1,  2},
		{0,  0},
		{0,  0},
		{0,  0},
		{7,  2},
		{0,  8},
		{0,  9},
		{0,  0},
		{0,  0},
		{0,  0},
		{0,  0}
	};

	static t_vec2int P1_terminal_shift_array = {
		{0,  0,  3,  4,  0,  0},
		{5,  6,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  3,  4,  0,  0},
		{0,  0,  3,  4,  0,  0},
		{0,  0,  3,  4,  0,  0},
		{5,  6,  0,  0, 10,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0}
	};

	static t_vec2int P1_reduce_array = {
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1,  0},
		{ 1,  1, -1, -1,  1,  1},
		{ 4,  4, -1, -1,  4,  4},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{ 2,  2, -1, -1,  2,  2},
		{ 3,  3, -1, -1,  3,  3},
		{ 5,  5, -1, -1,  5,  5}
	};


	// PART TWO: SLR(1)-class grammar:
	//
	//  R0: A' -> A terminator
	//  R1: A -> B
	//  R2: | A * B
	//  R3: B -> C
	//  R4: | B + C
	//  R5: C -> number
	//  R6: | ( A )
	//
	//  non-terminals: A, B, C
	//  terminals: * + number ( ) terminator

	static t_vecint P2_suffix_length_array = { 2, 1, 3, 1, 3, 1, 3 };
	static t_vecint P2_prefix_symbol_array = { -1, 0, 0, 1, 1, 2, 2 };

	static t_vec2int P2_non_terminal_shift_array = {
		{1,  2,  3},
		{0,  0,  0},
		{0,  0,  0},
		{0,  0,  0},
		{0,  0,  0},
		{8,  2,  3},
		{0,  9,  3},
		{0,  0, 10},
		{0,  0,  0},
		{0,  0,  0},
		{0,  0,  0},
		{0,  0,  0}
	};

	static t_vec2int P2_terminal_shift_array = {
		{0,  0,  4,  5,  0,  0},
		{6,  0,  0,  0,  0,  0},
		{0,  7,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  4,  5,  0,  0},
		{0,  0,  4,  5,  0,  0},
		{0,  0,  4,  5,  0,  0},
		{6,  0,  0,  0, 11,  0},
		{0,  7,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0}
	};

	static t_vec2int P2_reduce_array = {
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1,  0},
		{ 1, -1, -1, -1,  1,  1},
		{ 3,  3, -1, -1,  3,  3},
		{ 5,  5, -1, -1,  5,  5},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1},
		{ 2, -1, -1, -1,  2,  2},
		{ 4,  4, -1, -1,  4,  4},
		{ 6,  6, -1, -1,  6,  6}
	};


	// ---------------------------------------------------
	// tiny lexer, simplified: no error checking/reporting

	Lexer::Lexer(const string& input)
	:	_input(input), _position(0)
	{
	}

	LexAtom Lexer::get()
	{
		while (_position < _input.size() && _input[_position] == ' ')
			_position++;

		if (_position == _input.size())
			return LexAtom{ TerminalClass::trm_terminator, 0 };

		char ch = _input[_position++];
		if (ch == '*') return LexAtom{ TerminalClass::trm_mult, 0 };
		if (ch == '+') return LexAtom{ TerminalClass::trm_add, 0 };
		if (ch >= '0' && ch <= '9') return LexAtom{ TerminalClass::trm_number, int64_t(ch - '0') };
		if (ch == '(') return LexAtom{ TerminalClass::trm_lpar, 0 };
		if (ch == ')') return LexAtom{ TerminalClass::trm_rpar, 0 };
		return LexAtom{ TerminalClass::trm_terminator, 0 };
	}


	// ------------------------
	// generic semantic actions

	void sem_dummy(t_semantic_stack& stack)
	{
		(void)(stack);
	}

	void sem_mult(t_semantic_stack& stack)
	{
		LexAtom lhs = stack.top();
		stack.pop();
		stack.pop();
		LexAtom rhs = stack.top();
		stack.pop();
		stack.push(LexAtom{ TerminalClass::trm_number, lhs.value * rhs.value });
	}

	void sem_add(t_semantic_stack& stack)
	{
		LexAtom lhs = stack.top();
		stack.pop();
		stack.pop();
		LexAtom rhs = stack.top();
		stack.pop();
		stack.push(LexAtom{ TerminalClass::trm_number, lhs.value + rhs.value });
	}

	void sem_pars(t_semantic_stack& stack)
	{
		stack.pop();
		LexAtom number = stack.top();
		stack.pop();
		stack.pop();
		stack.push(number);
	}


	// ----------------------------------------------------------------
	// arrays of pointers to semantic actions in order of grammar rules 

	static vector<semantic_action_function> P1_semantic_actions =
	{
		&sem_dummy,
		&sem_dummy,
		&sem_mult,
		&sem_add,
		&sem_dummy,
		&sem_pars
	};

	static vector<semantic_action_function> P2_semantic_actions =
	{
		&sem_dummy,
		&sem_dummy,
		&sem_mult,
		&sem_dummy,
		&sem_add,
		&sem_dummy,
		&sem_pars
	};


	// --------------------------------------------------------------
	// generic LALR(1) parser, simplified: no syntax errors reporting

	Parser::Parser(const t_vecint& suffix_length_array,
		const t_vecint& prefix_symbol_array,
		const t_vec2int& non_terminal_shift_array,
		const t_vec2int& terminal_shift_array,
		const t_vec2int& reduce_array,
		const vector<semantic_action_function>& semantic_actions)
	:	_suffix_length_array(suffix_length_array),
		_prefix_symbol_array(prefix_symbol_array),
		_non_terminal_shift_array(non_terminal_shift_array),
		_terminal_shift_array(terminal_shift_array),
		_reduce_array(reduce_array),
		_semantic_actions(semantic_actions)
	{
	}

	int64_t Parser::execute(const string& input) const
	{
		Lexer lexer(input);
		t_semantic_stack semantic_stack;
		stack<int> parser_stack;
		int state = 0;
		parser_stack.push(state);

		bool acceptance = false;
		while (!acceptance)
		{
			LexAtom atom = lexer.get();
			int terminal = (int)atom.tclass;
			bool shift = false;
			while (!shift)
			{
				if (_reduce_array[state][terminal] == -1)
				{
					state = _terminal_shift_array[state][terminal];
					parser_stack.push(state);
					semantic_stack.push(atom);
					shift = true;
				}
				else
				{
					int rule = _reduce_array[state][terminal];
					if (rule == 0)
					{
						(*(_semantic_actions[rule]))(semantic_stack);
						acceptance = true;
						break;
					}

					int suffix_length = _suffix_length_array[rule];
					while (suffix_length && !parser_stack.empty())
					{
						parser_stack.pop();
						suffix_length--;
					}

					(*(_semantic_actions[rule]))(semantic_stack);

					state = _non_terminal_shift_array[parser_stack.top()][_prefix_symbol_array[rule]];
					parser_stack.push(state);
				}
			}
		}

		return semantic_stack.top().value;
	}


	// -------------------------------------------------------
	// use parser to calculate all expressions and sum results

	int64_t calculate_all(const vector<string>& input,
		const t_vecint& suffix_length_array,
		const t_vecint& prefix_symbol_array,
		const t_vec2int& non_terminal_shift_array,
		const t_vec2int& terminal_shift_array,
		const t_vec2int& reduce_array,
		const vector<semantic_action_function>& semantic_actions)
	{
		Parser parser(suffix_length_array, prefix_symbol_array, non_terminal_shift_array, terminal_shift_array, reduce_array, semantic_actions);
		return accumulate(input.begin(), input.end(), int64_t(0),
			[parser](int64_t sum, const string& s) { return sum + parser.execute(s); });
	}

	// ------------------------------------------
	// use appropriate arrays to configure parser

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return calculate_all(input, P1_suffix_length_array, P1_prefix_symbol_array,
			P1_non_terminal_shift_array, P1_terminal_shift_array, P1_reduce_array, P1_semantic_actions);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return calculate_all(input, P2_suffix_length_array, P2_prefix_symbol_array,
			P2_non_terminal_shift_array, P2_terminal_shift_array, P2_reduce_array, P2_semantic_actions);
	}
}
