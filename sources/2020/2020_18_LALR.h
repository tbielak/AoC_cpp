#ifndef __2020_18_LALR__
#define __2020_18_LALR__

#include "../shared/Solution.h"

namespace Day18_2020_LALR
{
	// ------------------------------------------------------------------------
	// BONUS: Alternative solution: tiny lexer + generic LALR(1) grammar parser
	// ------------------------------------------------------------------------

	typedef vector<int> t_vecint;
	typedef vector<vector<int>> t_vec2int;

	enum class TerminalClass { trm_mult, trm_add, trm_number, trm_lpar, trm_rpar, trm_terminator };

	struct LexAtom
	{
		TerminalClass tclass;
		int64_t value;
	};

	class Lexer
	{
	public:
		Lexer(const string& input);
		LexAtom get();

	private:
		string _input;
		size_t _position;
	};

	typedef stack<LexAtom> t_semantic_stack;
	typedef void (*semantic_action_function)(t_semantic_stack&);

	class Parser
	{
	public:
		Parser(const t_vecint& suffix_length_array,
			const t_vecint& prefix_symbol_array,
			const t_vec2int& non_terminal_shift_array,
			const t_vec2int& terminal_shift_array,
			const t_vec2int& reduce_array,
			const vector<semantic_action_function>& semantic_actions);

		int64_t execute(const string& input) const;

	private:
		const t_vecint& _suffix_length_array;
		const t_vecint& _prefix_symbol_array;
		const t_vec2int& _non_terminal_shift_array;
		const t_vec2int& _terminal_shift_array;
		const t_vec2int& _reduce_array;
		const vector<semantic_action_function>& _semantic_actions;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
