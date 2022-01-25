#include "2020_18.h"

namespace Day18_2020
{
	Expression::Expression(const t_TokenizedExpression& tokens)
	:	_tokens(tokens)
	{
	}

	// based on https://en.wikipedia.org/wiki/Shunting-yard_algorithm
	int64_t Expression::calculate(bool part_one)
	{
		for (const auto& t : _tokens)
		{
			if (t == ' ')
				continue;

			if (isdigit(t))
			{
				_values.push(int64_t(t) - int64_t('0'));
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

	t_vecTokenizedExpression Main::load(const vector<string>& input)
	{
		t_vecTokenizedExpression tokens;
		for (const auto& line : input)
			tokens.push_back(t_TokenizedExpression(line.begin(), line.end()));

		return tokens;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto tokens = load(input);
		return accumulate(tokens.begin(), tokens.end(), int64_t(0),
			[](int64_t sum, const auto& t) { return sum + Expression(t).calculate(true); });
	}
	
	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto tokens = load(input);
		return accumulate(tokens.begin(), tokens.end(), int64_t(0),
			[](int64_t sum, const auto& t) { return sum + Expression(t).calculate(false); });
	}
}
