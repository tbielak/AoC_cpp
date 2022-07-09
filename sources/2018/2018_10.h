#ifndef __2018_10__
#define __2018_10__

#include "../shared/Solution.h"

namespace Day10_2018
{
	class Points
	{
	public:
		void step();
		int height() const;
		vector<string> image() const;

		vector<int> x, y, vx, vy;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static Points load(const vector<string>& input);
	};
}

#endif
