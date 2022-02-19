#ifndef __2017_04__
#define __2017_04__

#include "../shared/Solution.h"

namespace Day04_2017
{
	typedef vector<string> t_passphrase;
	typedef vector<t_passphrase> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_data load(const vector<string>& input);
		static int valid_part_one(const t_passphrase& passphrase);
		static int valid_part_two(const t_passphrase& passphrase);
	};
}

#endif
