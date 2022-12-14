#include "2022_13.h"

namespace Day13_2022
{
	Element::Element(const string& input)
	:	_value(0), _is_value(false)
	{
		load(input, 1);
	}

	const string& Element::input() const
	{
		return _input;
	}

	int Element::compare(Element& right)	// left = this
	{
		int result = 0;
		while (1)
		{
			if (this->_is_value && right._is_value)
				return this->_value - right._value;

			if (!this->_is_value && !right._is_value)
			{
				size_t i = 0;
				size_t j = 0;
				while (i < this->_list.size() && j < right._list.size())
				{
					result = _list[i].compare(right._list[j]);
					if (result != 0)
						return result;

					i++;
					j++;
				}

				if (this->_list.size() == right._list.size())
					return result;

				return (int)this->_list.size() - (int)right._list.size();
			}

			this->convert_to_list();
			right.convert_to_list();
		}

		return result;
	}

	Element::Element()
	:	_value(0), _is_value(false)
	{
	}

	Element::Element(int value)
	:	_value(value), _is_value(true)
	{
	}

	size_t Element::load(string input, size_t pos)
	{
		_input = input;

		while (_input[pos] != ']')
		{
			if (_input[pos] == '[')	// beginning of the list
			{
				_list.push_back(Element());
				pos = _list.back().load(input, pos + 1);
			}
			else
				if (_input[pos] >= '0' && _input[pos] <= '9')	// number
				{
					size_t end = pos;
					while (_input[end] >= '0' && _input[end] <= '9') end++;
					_list.push_back(Element(stoi(_input.substr(pos, end - pos))));
					pos = end;
				}
				else
					pos++;	// must be comma
		}

		return pos + 1;	// end of list
	}

	void Element::convert_to_list()
	{
		if (_is_value)
		{
			_list.push_back(Element(_value));
			_is_value = false;
		}
	}
	
	AoC::Output Main::part_one(const vector<string>& input)
	{
		size_t sum = 0;
		for (size_t i = 0; i < input.size(); i += 3)
		{
			Element left(input[i]);
			Element right(input[i + 1]);
			if (left.compare(right) < 0)
				sum += ((i / 3) + 1);
		}

		return sum;
	}

	int Main::find(const vector<Element>& vec, const string& input)
	{
		int idx = 0;
		while (vec[idx].input() != input)
			idx++;

		return idx + 1;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		vector<Element> vec;
		for (const auto& s : input)
			if (s != "")
				vec.push_back(Element(s));

		vec.push_back(Element("[[2]]"));
		vec.push_back(Element("[[6]]"));
		sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.compare(b) < 0; });
		return find(vec, "[[2]]") * find(vec, "[[6]]");
	}
}
