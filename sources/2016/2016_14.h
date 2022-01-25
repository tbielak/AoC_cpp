#ifndef __2016_14__
#define __2016_14__

#include "../shared/Solution.h"

namespace Day14_2016
{
	typedef map<string, string> t_hash_cache;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static string md5(const string& hash);
		static string find_hash(t_hash_cache& cache, string input, int i, int additional_hashings);
		static char triplet(const string& hash);
		static bool funflet(char c, const string& hash);
		static int find_index(const string& input, int additional_hashings = 0);
	};
}

#endif
