#ifndef __2021_18_Pairs__
#define __2021_18_Pairs__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
