#ifndef __2015_18__
#define __2015_18__

#include "../shared/Solution.h"

namespace Day18_2015
{
	class Lights
	{
	public:
		Lights(const vector<string>& lt);

		void animate(int part, int steps);
		int count_on();

	private:
		vector<string> _lt;
		int _width, _height;

		void stuck();
		int neighbours(const vector<string>& ref, int x, int y);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);
	};
}

#endif
