#include "2020_05.h"

namespace Day05_2020
{
	Boarding::Boarding(const vector<string>& input)
	{
		_maxr = -1;
		_maxc = -1;
		for (const auto& s : input)
		{
			int r = binary_search(s.substr(0, 7), 'F');
			int c = binary_search(s.substr(7, 3), 'L');
			_seats.push_back(make_pair(r, c));
			_maxr = max(_maxr, r);
			_maxc = max(_maxc, c);
		}
	}

	int Boarding::max_sid() const
	{
		int msid = -1;
		for (const auto& s : _seats)
		{
			int sid = s.first * 8 + s.second;
			msid = max(msid, sid);
		}

		return msid;
	}

	int Boarding::my_seat_sid() const
	{
		std::vector<bool> taken((_maxr + 1) * (_maxc + 1));
		for (const auto& s : _seats)
			taken[s.first * 8 + s.second] = true;

		for (size_t i = _maxc; i < taken.size() - 1; i++)
			if (taken[i - 1] && !taken[i] && taken[i + 1])
				return (int)i;

		return -1;
	}

	int Boarding::binary_search(const string& s, char direction)
	{
		int left = 0;
		int right = (1 << s.size()) - 1;
		for (auto c : s)
		{
			int vm = (right - left + 1) / 2;
			if (c == direction) right -= vm; else left += vm;
		}

		return left;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Boarding(input).max_sid();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Boarding(input).my_seat_sid();
	}
}
