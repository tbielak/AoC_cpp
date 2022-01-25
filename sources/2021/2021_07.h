#ifndef __2021_07__
#define __2021_07__

#include "../shared/Solution.h"

namespace Day07_2021
{
	typedef vector<int> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static t_data load(const string& input);

		int iabs(int v) const;
		
		template<typename Functor>
		int calculate_fuel(const t_data& x, Functor ftor) const;
	};
}

#endif
