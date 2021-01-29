#ifndef __CUDA_MISC__
#define __CUDA_MISC__

#include "Console.h"

namespace CUDA
{
    extern int mp;
    extern int cores_mp;
    extern int cores_total;

	void setup(AoC::Console& cc);
}

#endif
