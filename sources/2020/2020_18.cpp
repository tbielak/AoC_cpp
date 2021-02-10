#include "2020_18.h"

namespace Day18_2020
{
	Expression::Expression(const t_TokenizedExpression& tokens)
	:	_tokens(tokens)
	{
	}

	// based on https://en.wikipedia.org/wiki/Shunting-yard_algorithm
	uintmax_t Expression::calculate(bool part_one)
	{
		for (const auto& t : _tokens)
		{
			if (t == ' ')
				continue;

			if (isdigit(t))
			{
				_values.push(uintmax_t(t) - uintmax_t('0'));
				continue;
			}

			if (t == '+' || t == '*')
			{
				while (_ops.size() > 0 && _ops.top() != '(')
				{
					if (!part_one && (t != '*' || _ops.top() != '+'))	// strange precedence
						break;

					reduce();
				}

				_ops.push(t);
				continue;
			}

			if (t == '(')
			{
				_ops.push(t);
				continue;
			}

			if (t == ')')
			{
				while (_ops.size() > 0 && _ops.top() != '(')
					reduce();

				if (_ops.top() == '(')
					_ops.pop();
			}
		}

		while (_ops.size() > 0)
			reduce();

		return _values.top();
	}

	void Expression::reduce()
	{
		const auto lhs = _values.top();
		_values.pop();

		const auto rhs = _values.top();
		_values.pop();

		if (_ops.top() == '+')
			_values.push(lhs + rhs);
		else
			_values.push(lhs * rhs);

		_ops.pop();
	}
	
	pair<uintmax_t, uintmax_t> both_parts(const t_vecTokenizedExpression& input)
	{
		uintmax_t s1 = 0;
		uintmax_t s2 = 0;
		for (const auto& tokens : input)
		{
			Expression expr(tokens);
			s1 += expr.calculate(true);
			s2 += expr.calculate(false);
		}

		return make_pair(s1, s2);
	}

	t_output main(const t_input& input)
	{
		t_vecTokenizedExpression tokens;
		for (const auto& line : input)
			tokens.push_back(t_TokenizedExpression(line.begin(), line.end()));

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(tokens);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
