#ifndef __2020_18__
#define __2020_18__

#include "../shared/input_output.h"

namespace Day18_2020
{
	typedef vector<char> t_TokenizedExpression;
	typedef vector<t_TokenizedExpression> t_vecTokenizedExpression;

	class Expression
	{
	public:
		Expression(const t_TokenizedExpression& tokens);

		uintmax_t calculate(bool part_one);

	private:
		t_TokenizedExpression _tokens;
		stack<char> _ops;
		stack<uintmax_t> _values;

		void reduce();
	};

	t_output main(const t_input& input);
}

#endif
