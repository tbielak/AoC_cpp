#ifndef __2019_03__
#define __2019_03__

#include "../shared/Solution.h"

namespace Day03_2019
{
	class Wire
	{
	public:
		Wire(const string& input);
		
		void twists_and_turns();
		int distance_to_closest(const Wire& other);
		int fewest_steps(const Wire& other);

	private:
		vector<pair<char, int>> _path;
		map<pair<int, int>, int> _points;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);
	};
}

#endif
