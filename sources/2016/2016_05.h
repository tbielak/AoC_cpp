#ifndef __2016_05__
#define __2016_05__

#include "../shared/input_output.h"

namespace Day05_2016
{
	class MD5_Computing_Engine
	{
	public:
		MD5_Computing_Engine(const string& line, bool part_two);

		string run();

	private:
		string _line;
		int _n;
		int _start;
		int _batch_size;
		bool _part_two;
		string _result;
		vector<thread*> _threads;
		map<int, int> _found;		// step number to result found
		mutex _m;

		static void worker(MD5_Computing_Engine* engine);

		void calculate();
		int get_starting_point();
		
		char to_hex(int v) const;
		void set_result_part_one(int step, unsigned int value);
		void set_result_part_two(int step, unsigned int value);
	};

	t_output main(const t_input& input);
}

#endif
