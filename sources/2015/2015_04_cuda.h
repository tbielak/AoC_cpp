#ifndef __2015_04_CUDA__
#define __2015_04_CUDA__

#include "../shared/Solution.h"

// routines delivered by NVidia CUDA compiler
extern bool Day_04_2015_CUDA_input(const char* input, int input_length);
extern bool Day_04_2015_CUDA_md5Check(int blocksPerGrid, int threadsPerBlock, unsigned char* results, unsigned int result_mask, int starting_point);

namespace Day04_2015_CUDA
{
	class MD5_Computing_Engine
	{
	public:
		MD5_Computing_Engine();
		~MD5_Computing_Engine();
		
		bool set_input(const string& line);
		int run(unsigned int digest_mask);

	private:
		unsigned char* _host_results;
		unsigned char* _cuda_results;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
