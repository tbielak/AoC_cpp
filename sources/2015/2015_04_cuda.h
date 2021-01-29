#ifndef __2015_04_CUDA__
#define __2015_04_CUDA__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
