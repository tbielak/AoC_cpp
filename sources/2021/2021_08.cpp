#include "2021_08.h"

namespace Day08_2021
{
	Entry::Entry(string s)
	{
		for (int i = 0; i < 10; i++)
		{
			string signal = read_input(s);

			// signal with two segments must be digit 1
			if (signal.size() == 2)
				_one = signal;

			// signal with four segments must be digit 4
			if (signal.size() == 4)
				_four = signal;
		}

		s = s.substr(2);

		for (int i = 0; i < 4; i++)
			_digits.push_back(read_input(s));
	}

	int Entry::count_digits_1478() const
	{
		return (int)count_if(_digits.begin(), _digits.end(),
			[](const auto& d) { return d.size() == 2 || d.size() == 3 || d.size() == 4 || d.size() == 7; });
	}

	int Entry::find_number() const
	{
		return (int)accumulate(_digits.begin(), _digits.end(), 0,
			[this](int n, const auto& d) { return n * 10 + get(d); });
	}

	// number of segments of a digit (if positive value, see below)
	const vector<int> Entry::_segment_count = { -1, -1, 1, 7, 4, -5, -6, 8 };

	int Entry::get(const string& digit) const
	{
		// return 1, 4, 7 and 8 taking into account number of segments only
		int d = _segment_count[digit.size()];
		if (d > 0)
			return d;

		// when digit has five segments...
		if (d == -5)
		{
			// it is 3 when it shares two segments with 1
			if (count(_one, digit) == 2)
				return 3;

			// it is 5 when it shares three segments with 4
			if (count(_four, digit) == 3)
				return 5;

			// otherwise it has to be 2
			return 2;
		}

		// when digit has six segments...
		if (d == -6)
		{
			// it is 6 when it shares one segment with 1
			if (count(_one, digit) == 1)
				return 6;

			// it is 9 when it shares four segments with 4
			if (count(_four, digit) == 4)
				return 9;

			// otherwise it has to be 0
			return 0;
		}

		return -1;	// unreachable
	}

	int Entry::count(const string& src, const string& target) const
	{
		// how many segments of src can be found in target?
		return (int)count_if(src.begin(), src.end(),
			[target](auto v) { return target.find(v) != string::npos; });
	}

	string Entry::read_input(string& input)
	{
		size_t pos = input.find(" ");
		string s = input.substr(0, pos);
		input = input.substr(pos + 1);
		return s;
	}

	t_entries Main::load(const vector <string>& input)
	{
		t_entries e;
		for (const auto& s : input)
			e.push_back(Entry(s));

		return e;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto entries = load(input);
		return accumulate(entries.begin(), entries.end(), 0, [](int sum, const auto& e) { return sum + e.count_digits_1478(); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto entries = load(input);
		return accumulate(entries.begin(), entries.end(), 0, [](int sum, const auto& e) { return sum + e.find_number(); });
	}
}
