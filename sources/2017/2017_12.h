#ifndef __2017_12__
#define __2017_12__

#include "../shared/Solution.h"

namespace Day12_2017
{
	typedef set<int> t_programs;
	typedef map<int, t_programs> t_connections;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_programs load(const string& input);
		static t_connections load(const vector<string>& input);
		static t_programs find_group(const t_connections& connections, int group);
	};
}

#endif
