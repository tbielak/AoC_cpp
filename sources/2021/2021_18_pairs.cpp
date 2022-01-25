#include "2021_18_pairs.h"

namespace Day18_2021_Pairs
{
	Number::Number(const string& s)
	{
		size_t pos = 0;
		load(s, pos, 0);
	}

	void Number::add(const Number& n)
	{
		for (auto& p : _parts)
			p.level++;

		for (const auto& p : n._parts)
			_parts.push_back({ p.level + 1, p.value });

		reduce();
	}

	int Number::magnitude()
	{
		while (_parts.size() > 1)
		{
			for (int i = 0; i < (int)_parts.size() - 1; i++)
				if (_parts[i].level == _parts[i + 1].level)
				{
					_parts[i].value = _parts[i].value * 3 + _parts[i + 1].value * 2;
					_parts[i].level--;
					_parts.erase(_parts.begin() + i + 1);
					break;
				}
		}

		return _parts[0].value;
	}

	void Number::load(const string& s, size_t& pos, int level)
	{
		for (int i = 0; i < 2; i++)
		{
			if (s[pos] == '[')
				load(s, ++pos, level + 1);
			else
				_parts.push_back({ level, int(s[pos++] - '0') });

			if (pos == s.size())
				return;

			pos++;	// skip ',' (for i == 0) or ']' (for i == 1)
		}
	}

	int Number::can_explode()
	{
		for (int i = 0; i < (int)_parts.size() - 1; i++)
			if (_parts[i].level == 5)
				return i;

		return -1;
	}

	bool Number::explode()
	{
		int pos = can_explode();
		if (pos == -1)
			return false;

		if (pos > 0)
			_parts[pos - 1].value += _parts[pos].value;

		if (pos < (int)_parts.size() - 2)
			_parts[pos + 2].value += _parts[pos + 1].value;

		_parts.erase(_parts.begin() + pos);
		_parts[pos].level--;
		_parts[pos].value = 0;
		return true;
	}

	bool Number::split()
	{
		for (int i = 0; i < (int)_parts.size(); i++)
			if (_parts[i].value >= 10)
			{
				int v2 = _parts[i].value / 2;
				_parts.insert(_parts.begin() + i, { _parts[i].level + 1, v2 });
				_parts[i + 1].level++;
				_parts[i + 1].value -= v2;
				return true;
			}

		return false;
	}

	void Number::reduce()
	{
		while (1)
			if (!explode() && !split())
				return;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		Number n(input[0]);
		for (size_t i = 1; i < input.size(); i++)
			n.add(Number(input[i]));

		return n.magnitude();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int largest = 0;

		for (size_t i = 0; i < input.size(); i++)
			for (size_t j = 0; j < input.size(); j++)
				if (i != j)
				{
					Number n(input[i]);
					n.add(input[j]);
					int mag = n.magnitude();
					largest = max(largest, mag);
				}

		return largest;
	}
}
