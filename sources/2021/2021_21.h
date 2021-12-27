#ifndef __2021_21__
#define __2021_21__

#include "../shared/input_output.h"

namespace Day21_2021
{
	// dedicated class for pair of ints
	// because we need to access them using [] operator
	class Pair
	{
	public:
		Pair(int64_t p0 = 0, int64_t p1 = 0);
		
		int64_t& operator[] (int idx);
		int64_t operator[] (int idx) const;
		bool operator < (const Pair& rhs) const;

	private:
		int64_t _v[2];
	};

	// structures dedicated for part two:
	// cache:
	typedef tuple<int, Pair, Pair> t_cacheKey;	// key: player, position, score
	typedef map<t_cacheKey, Pair> t_cache;		// value: 1st and 2nd player win count

	struct Result      // see static results variable in cpp file
	{
		int points;
		int paths;
	};

	t_output main(const t_input& input);
}

#endif
