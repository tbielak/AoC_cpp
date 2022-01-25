#ifndef __2015_04_MT__
#define __2015_04_MT__

#include "../shared/Solution.h"

namespace Day04_2015_MT
{
	class MD5_Computing_Engine
	{
	public:
		MD5_Computing_Engine(const string& line, unsigned int result_mask);

		int run();

	private:
		string _line;
		unsigned int _result_mask;
		int _n;
		int _start;
		int _batch_size;
		int _result;
		vector<thread*> _threads;
		mutex _m;

		static void worker(MD5_Computing_Engine* engine);
		
		void calculate();
		int get_starting_point();
		void set_result(int value);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
