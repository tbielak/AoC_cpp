#include "2020_23.h"

namespace Day23_2020
{
	Cup::Cup(size_t label)
	:	label(label), next(0)
	{
	}

	CrabCups::CrabCups(const string& input, size_t expand_to)
	{
		_first = 0;
		_count = max(input.size(), expand_to);
		_cups = vector<Cup*>(_count);

		for (size_t i = 0; i < _count; i++)
		{
			size_t label = i < input.size() ? size_t(input[i]) - '0' : i + 1;
			_cups[i] = new Cup(label);
			if (label == 1)
				_first = _cups[i];
		}

		for (size_t i = 0; i < _count - 1; i++)
			_cups[i]->next = _cups[i + 1];

		_cups[_count - 1]->next = _cups[0];

		_ordered = vector<Cup*>(_count);
		for (const auto p : _cups)
			_ordered[p->label - 1] = p;
	}

	CrabCups::~CrabCups()
	{
		for (auto& cup : _cups)
			delete cup;
	}

	inline size_t CrabCups::previous(size_t x)
	{
		return ((x + _count - 2) % _count) + 1;
	}

	CrabCups& CrabCups::play(size_t round_count)
	{
		Cup* current = _cups[0];
		for (size_t r = 0; r < round_count; r++)
		{
			Cup* pick = current->next;
			size_t dest = previous(current->label);

			while (pick->label == dest || pick->next->label == dest || pick->next->next->label == dest)
				dest = previous(dest);

			current->next = pick->next->next->next;
			pick->next->next->next = _ordered[dest - 1]->next;
			_ordered[dest - 1]->next = pick;
			current = current->next;
		}

		return *this;
	}

	string CrabCups::clockwise() const
	{
		string s;
		Cup* cur = _first;
		for (cur = cur->next; cur != _first; cur = cur->next)
			s += to_string(cur->label);

		return s;
	}

	int64_t CrabCups::mul() const
	{
		return int64_t(_first->next->label) * int64_t(_first->next->next->label);
	}

	AoC::Output Main::part_one(const string& input)
	{
		return CrabCups(input, 0).play(100).clockwise();
	}

	AoC::Output Main::part_two(const string& input)
	{
		return CrabCups(input, 1000000).play(10000000).mul();
	}
}
