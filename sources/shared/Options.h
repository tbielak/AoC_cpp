#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "stl.h"

namespace AoC
{
	class Options
	{
	public:
		Options();
		void parse(int argc, char* argv[]);

		bool colors;
		bool help;
		bool available;
		int speed;
		int day;
		int solution;
		string input_filename;

	private:
		void get_speed(const string& s);
		void which_puzzle(const string& s);
	};
}

#endif
