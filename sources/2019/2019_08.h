#ifndef __2019_08__
#define __2019_08__

#include "../shared/Solution.h"

namespace Day08_2019
{
	typedef vector<string> t_image;
	typedef vector<t_image> t_layers;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static t_layers load(const string& input);
	};
}

#endif
