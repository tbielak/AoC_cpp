#ifndef __2020_18__
#define __2020_18__

#include "../shared/Solution.h"

namespace Day18_2020
{
	typedef vector<char> t_TokenizedExpression;
	typedef vector<t_TokenizedExpression> t_vecTokenizedExpression;

	class Expression
	{
	public:
		Expression(const t_TokenizedExpression& tokens);

		int64_t calculate(bool part_one);

	private:
		t_TokenizedExpression _tokens;
		stack<char> _ops;
		stack<int64_t> _values;

		void reduce();
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_vecTokenizedExpression load(const vector<string>& input);
	};
}

#endif
