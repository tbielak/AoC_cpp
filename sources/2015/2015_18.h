#ifndef __2015_18__
#define __2015_18__

#include "../shared/input_output.h"

namespace Day18_2015
{
	class Lights
	{
	public:
		Lights(const vector<string>& lt);

		void animate(int part, int steps);
		size_t count_on();

	private:
		vector<string> _lt;
		int _width, _height;

		void stuck();
		int neighbours(const vector<string>& ref, int x, int y);
	};

	t_output main(const t_input& input);
}

#endif
