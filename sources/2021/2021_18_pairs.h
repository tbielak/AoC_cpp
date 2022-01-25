#ifndef __2021_18_Pairs__
#define __2021_18_Pairs__

#include "../shared/Solution.h"

namespace Day18_2021_Pairs
{
	struct Part
	{
		int level;
		int value;
	};

	class Number
	{
	public:
		Number(const string& s);
		
		void add(const Number& n);
		int magnitude();

	private:
		vector<Part> _parts;

		void load(const string& s, size_t& pos, int level);

		int can_explode();
		bool explode();
		bool split();
		void reduce();
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
