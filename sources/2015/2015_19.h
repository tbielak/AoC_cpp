#ifndef __2015_19__
#define __2015_19__

#include "../shared/Solution.h"

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

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void load(const vector<string>& input, string& molecule, t_vecReplacement& replacements);
	};
}

#endif
