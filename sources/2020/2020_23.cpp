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

	void CrabCups::play(size_t round_count)
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
	}

	string CrabCups::clockwise() const
	{
		string s;
		Cup* cur = _first;
		for (cur = cur->next; cur != _first; cur = cur->next)
			s += to_string(cur->label);

		return s;
	}

	uintmax_t CrabCups::mul() const
	{
		return uintmax_t(_first->next->label) * uintmax_t(_first->next->next->label);
	}

	string part_one(const string& input)
	{
		CrabCups cc(input, 0);
		cc.play(100);
		return cc.clockwise();
	}

	uintmax_t part_two(const string& input)
	{
		CrabCups cc(input, 1000000);
		cc.play(10000000);
		return cc.mul();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input[0]);
		auto p2 = part_two(input[0]);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(p1);
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
