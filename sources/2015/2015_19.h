#ifndef __2015_19__
#define __2015_19__

#include "../shared/input_output.h"

namespace Day19_2015
{
	class Replacement
	{
	public:
		Replacement(const string& src, const string& dst);
		
		string src, dst;
		int random;
	};

	typedef vector<Replacement> t_vecReplacement;

	t_output main(const t_input& input);
}

#endif
