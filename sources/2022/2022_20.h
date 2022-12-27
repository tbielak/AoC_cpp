#ifndef __2022_20__
#define __2022_20__

#include "../shared/Solution.h"

namespace Day20_2022
{
	class Data
	{
	public:
		Data(const vector<string>& input, int64_t decryption_key = 1);
		int64_t decode(int rounds = 1);

	private:
		vector<pair<int, int64_t>> _data;
		int _size;
		int _zero_idx;

		int64_t target(int64_t a, int64_t b) const;
		int64_t get(int idx) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
