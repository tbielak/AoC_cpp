#include "2015_04_MT.h"

// the function specified below is already defined in 2015_04.cpp code (see #include "2015_04_shared.h")
// that's why we only need extern here
extern unsigned int Day_04_2015_CPU_md5_single_transform(unsigned int* x);

namespace Day04_2015_MT
{
	MD5_Computing_Engine::MD5_Computing_Engine(const string& line, unsigned int result_mask)
	:	_line(line), _result_mask(result_mask), _start(1), _batch_size(1000), _result(-1)
	{
		_n = (int)thread::hardware_concurrency();
		_threads = vector<thread*>(_n);
	}

	int MD5_Computing_Engine::run()
	{
		for (int t = 0; t < _n; t++)
			_threads[t] = new thread(worker, this);

		for (auto t : _threads)
			t->join();

		for (auto t : _threads)
			delete t;

		return _result;
	}

	void MD5_Computing_Engine::worker(MD5_Computing_Engine* engine)
	{
		engine->calculate();
	}
	
	void MD5_Computing_Engine::calculate()
	{
		while (1)
		{
			int start = get_starting_point();
			if (start == -1)
				return;  // result found by the other thread

			for (int i = start; i < start + _batch_size; i++)
			{
				// prepare input
				string input = _line + to_string(i);

				// copy input to 64-byte buffer, required for single MD5 transform
				vector<unsigned char> buffer(64, 0);
				copy(input.begin(), input.end(), buffer.begin());

				// place 0x80 at the end of the string to create correct MD5 padding
				buffer[input.size()] = 0x80;

				// place length (in bits) of the string at 56th buffer element, as required by MD5 padding
				buffer[56] = unsigned char(input.size() * 8);

				// do one MD5 transform and get part of MD5 hash
				unsigned int result = Day_04_2015_CPU_md5_single_transform((unsigned int*)(&buffer[0]));

				// check requested number of zeros
				if ((result & _result_mask) == result)
				{
					set_result(i); // result found
					return;
				}
			}
		}
	}

	int MD5_Computing_Engine::get_starting_point()
	{
		lock_guard<mutex> guard(_m);
		if (_result != -1)
			return -1;  // work done

		int start = _start;
		_start += _batch_size;
		return start;
	}

	void MD5_Computing_Engine::set_result(int value)
	{
		lock_guard<mutex> guard(_m);
		_result = (_result == -1) ? value : min(_result, value);
	}

	int both_parts(int part, const string& line)
	{
		const vector<unsigned int> result_mask = { 0xff0f0000, 0xff000000 };
		MD5_Computing_Engine engine(line, result_mask[part - 1]);
		return engine.run();
	}

	t_output main(const t_input& input)
	{
		string line = input[0];
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = both_parts(1, line);
		auto p2 = both_parts(2, line);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
