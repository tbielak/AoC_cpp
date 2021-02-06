#include "2015_24_CUDA.h"
#include <cuda_runtime.h>
#include <memory.h>

namespace Day24_2015_CUDA
{
	QEEngine::QEEngine(const t_input& input)
	:	_threadsPerBlock(0), _blocksPerGrid(0), _groupsPerThread(0),
		_cuda_results(0), _cuda_aggregated(0), _host_aggregated(0), _cuda_minQE(0), _host_minQE(0)
	{
		for (const auto& line : input)
			_input.push_back(stoi(line));
	}

	QEEngine::~QEEngine()
	{
		cudaFree(_cuda_results);
		cudaFree(_cuda_aggregated);
		free(_host_aggregated);
		cudaFree(_cuda_minQE);
		free(_host_minQE);
	}

	bool QEEngine::init()
	{
		if (_input.size() < 10)
		{
			cout << "ERROR: number of packages too low to bother CUDA, use standard solution ;-)" << endl;
			return false;
		}

		if (_input.size() > 31)
		{
			cout << "ERROR: too many packages, unable to solve the puzzle" << endl;
			return false;
		}

		int tpb = 8;
		int tmp = (int)_input.size() - tpb;
		int bpg = (tmp / 2);
		if (bpg > 2) bpg--;
		int gpt = tmp - bpg;

		// threads configuration
		_threadsPerBlock = (1 << tpb);
		_blocksPerGrid = (1 << bpg);
		_groupsPerThread = (1 << gpt);

		// CUDA device memory keeping results
		int group_count = _threadsPerBlock * _blocksPerGrid * _groupsPerThread;
		if (cudaMalloc((void**)&_cuda_results, group_count) != cudaSuccess)
		{
			cout << "ERROR: out of memory on CUDA device" << endl;
			return false;
		}

		// CUDA device memory keeping aggregated results
		int concurrent_groups = _threadsPerBlock * _blocksPerGrid;
		if (cudaMalloc((void**)&_cuda_aggregated, concurrent_groups) != cudaSuccess)
		{
			cout << "ERROR: out of memory on CUDA device" << endl;
			return false;
		}

		// host memory keeping aggregated results
		_host_aggregated = (unsigned char *)::malloc(concurrent_groups);
		if (_host_aggregated == 0)
		{
			cout << "ERROR: out of host memory" << endl;
			return false;
		}

		// CUDA device memory keeping min QE
		if (cudaMalloc((void**)&_cuda_minQE, concurrent_groups * sizeof(long long)) != cudaSuccess)
		{
			cout << "ERROR: out of memory on CUDA device" << endl;
			return false;
		}

		// host memory keeping min QE
		_host_minQE = (long long *)::malloc(concurrent_groups * sizeof(long long));
		if (_host_minQE == 0)
		{
			cout << "ERROR: out of host memory" << endl;
			return false;
		}

		int cuda_input[32];
		for (size_t i = 0; i < _input.size(); i++)
			cuda_input[i] = _input[i];

		// store input in CUDA device constant memory
		if (!Day_04_2015_CUDA_input(cuda_input))
		{
			cout << "ERROR: unable to store puzzle input in device constant memory" << endl;
			return false;
		}

		return true;
	}

	intmax_t QEEngine::run(int split)
	{
		// find requested packages weight
		int packages_weight = accumulate(_input.begin(), _input.end(), 0) / split;

		// find groups meeting the criteria
		if (!Day_24_2015_CUDA_findGroups(_blocksPerGrid, _threadsPerBlock, _groupsPerThread, _cuda_results, (int)_input.size(), packages_weight))
		{
			cout << "ERROR: failed to launch CUDA kernel routine" << endl;
			return -1;
		}

		// aggregate results
		if (!Day_24_2015_CUDA_findGroupsMin(_blocksPerGrid, _threadsPerBlock, _groupsPerThread, _cuda_results, _cuda_aggregated))
		{
			cout << "ERROR: failed to launch CUDA kernel routine" << endl;
			return -1;
		}

		// copy aggregated results from device memory to the host memory
		int concurrent_groups = _threadsPerBlock * _blocksPerGrid;
		if (cudaMemcpy(_host_aggregated, _cuda_aggregated, concurrent_groups, cudaMemcpyDeviceToHost) != cudaSuccess)
		{
			cout << "ERROR: memcpy failed" << endl;
			return -1;
		}

		// find minimum packages count in the group
		unsigned char minimum_packages_count = 0xff;
		for (int i = 0; i < concurrent_groups; i++)
			if (minimum_packages_count > _host_aggregated[i])
				minimum_packages_count = _host_aggregated[i];

		// find min QE for groups with minimal packages count
		if (!Day_24_2015_CUDA_findQEMin(_blocksPerGrid, _threadsPerBlock, _groupsPerThread, _cuda_results, _cuda_minQE, (int)_input.size(), minimum_packages_count))
		{
			cout << "ERROR: failed to launch CUDA kernel routine" << endl;
			return -1;
		}

		// copy minQE from device memory to the host memory
		if (cudaMemcpy(_host_minQE, _cuda_minQE, concurrent_groups * sizeof(long long), cudaMemcpyDeviceToHost) != cudaSuccess)
		{
			cout << "ERROR: memcpy failed" << endl;
			return -1;
		}

		// aggregate minQE result
		long long minQE = 0x7fffffffffffffff;
		for (int i = 0; i < concurrent_groups; i++)
			if (minQE > _host_minQE[i])
				minQE = _host_minQE[i];

		return minQE;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		QEEngine engine(input);
		intmax_t p1 = -1;
		intmax_t p2 = -1;
		if (engine.init())
		{
			p1 = engine.run(3);
			p2 = engine.run(4);
		}
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
