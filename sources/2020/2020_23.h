#ifndef __2020_23__
#define __2020_23__

#include "../shared/Solution.h"

namespace Day23_2020
{
	class Cup
	{
	public:
		Cup(size_t label);

		size_t label;
		Cup* next;
	};

	class CrabCups
	{
	public:
		CrabCups(const string& input, size_t expand_to);
		~CrabCups();

		inline size_t previous(size_t x);

		CrabCups& play(size_t round_count);

		string clockwise() const;
		int64_t mul() const;

	private:
		size_t _count;
		Cup* _first;
		vector<Cup*> _cups;
		vector<Cup*> _ordered;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
