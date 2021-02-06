#include "2015_04_CUDA.h"
#include <cuda_runtime.h>
#include <memory.h>

namespace Day04_2015_CUDA
{
	MD5_Computing_Engine::MD5_Computing_Engine()
	:	_host_results(0), _cuda_results(0)
	{
	}

	MD5_Computing_Engine::~MD5_Computing_Engine()
	{
		free(_host_results);
		cudaFree(_cuda_results);
	}

	bool MD5_Computing_Engine::set_input(const string& line)
	{
		return Day_04_2015_CUDA_input(line.c_str(), (int)line.size());
	}

	int MD5_Computing_Engine::run(unsigned int digest_mask)
	{
		constexpr int threadsPerBlock = 256;
		constexpr int blocksPerGrid = 2048;
		constexpr int elements = threadsPerBlock * blocksPerGrid;

		// results:
		// every byte is a result of one input generated by single CUDA thread
		// =1: input meets the criteria (requested number of MD5 hash zeros), =0: otherwise

		// host memory keeping results
		_host_results = (unsigned char*)::malloc(elements);
		if (_host_results == 0)
		{
			cout << "ERROR: out of host memory" << endl;
			return -1;
		}

		// CUDA device memory keeping results
		if (cudaMalloc((void**)&_cuda_results, elements) != cudaSuccess)
		{
			cout << "ERROR: out of memory on CUDA device" << endl;
			return -1;
		}

		// find solution
		int ret = -1;
		int starting_point = 0;
		while (ret == -1)
		{
			// launch CUDA kernel routine
			if (!Day_04_2015_CUDA_md5Check(blocksPerGrid, threadsPerBlock, _cuda_results, digest_mask, starting_point))
			{
				cout << "ERROR: failed to launch CUDA kernel routine" << endl;
				return -1;
			}

			// copy results from device memory to the host memory
			if (cudaMemcpy(_host_results, _cuda_results, elements, cudaMemcpyDeviceToHost) != cudaSuccess)
			{
				cout << "ERROR: memcpy failed" << endl;
				return -1;
			}

			// find solution
			int i = starting_point == 0 ? 1 : 0;
			for (; i < elements; i++)
				if (_host_results[i] != 0)
					return i + starting_point;

			// not found -> next batch
			starting_point += elements;
		}

		return -1;
	}

	t_output main(const t_input& input)
	{
		string line = input[0];

		auto t0 = chrono::steady_clock::now();
		MD5_Computing_Engine engine;
		int p1 = -1;
		int p2 = -1;
		if (engine.set_input(line))
		{
			p1 = engine.run(0xff0f0000);
			p2 = engine.run(0xff000000);
		}
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
