#include "2016_05.h"

// use code shared between 2015 and 2016 solutions
#define MD5_SINGLE_TRANSFORM_PREFIX
#define MD5_SINGLE_TRANSFORM_FNAME Day_05_2016_md5_single_transform
#include "../MD5/MD5_single_transform.h"

namespace Day05_2016
{
	MD5_Computing_Engine::MD5_Computing_Engine(const string& line, bool part_two)
	:   _line(line), _start(1), _batch_size(1000), _part_two(part_two)
	{
		_n = (int)thread::hardware_concurrency();
		_threads = vector<thread*>(_n);
	}

	string MD5_Computing_Engine::run()
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
				return;  // task completed (by the other threads)

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
				buffer[56] = (unsigned char)(input.size() * 8);

				// do one MD5 transform and get part of MD5 hash
				unsigned int result = MD5_SINGLE_TRANSFORM_FNAME((unsigned int*)(&buffer[0]));

				// check five zeros
				if ((result & 0xff0f0000) == result)
				{
					if (_part_two)
						set_result_part_two(i, result);
					else
						set_result_part_one(i, result);
				}
			}
		}
	}

	int MD5_Computing_Engine::get_starting_point()
	{
		lock_guard<mutex> guard(_m);
		if (_result.size() > 0)
			return -1;  // work done

		int start = _start;
		_start += _batch_size;
		return start;
	}

	char MD5_Computing_Engine::to_hex(int v) const
	{
		return (v < 10) ? char(v + '0') : char(v - 10 + 'a');
	}

	void MD5_Computing_Engine::set_result_part_one(int step, unsigned int value)
	{
		lock_guard<mutex> guard(_m);

		// store result
		_found[step] = value;
		if (_found.size() < 8)
			return;
		
		// put them in correct order
		for (const auto& p : _found)
			_result += to_hex((p.second & 0x000f0000) >> 16);
	}

	void MD5_Computing_Engine::set_result_part_two(int step, unsigned int value)
	{
		lock_guard<mutex> guard(_m);

		// store result
		_found[step] = value;
		if (_found.size() < 8)
			return;

		// process them in correct order, try to solve
		string candidate = "????????";
		for (const auto& p : _found)
		{
			int position = (p.second & 0x000f0000) >> 16;
			if (position < 8 && candidate[position] == '?')
				candidate[position] = to_hex((p.second & 0xf0000000) >> 28);
		}

		// all known?
		if (candidate.find_first_of('?') == string::npos)
			_result = candidate;
	}

	string part_one(const string& line)
	{
		MD5_Computing_Engine engine(line, false);
		return engine.run();
	}

	string part_two(const string& line)
	{
		MD5_Computing_Engine engine(line, true);
		return engine.run();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input[0]);
		auto p2 = part_two(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(p1);
		solutions.push_back(p2);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}

// undefine macros
#undef MD5_SINGLE_TRANSFORM_PREFIX
#undef MD5_SINGLE_TRANSFORM_FNAME
