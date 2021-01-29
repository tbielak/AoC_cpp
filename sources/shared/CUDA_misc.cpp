#include "CUDA_misc.h"
#include <cuda_runtime.h>

namespace CUDA
{
    int mp = 0;
    int cores_mp = 0;
    int cores_total = 0;

    // note: must be the same list as architectures list specified in project options (see: CUDA C/C++/Device/Code Generation)
    const map<int, int> archCores = {
        {0x35, 192}, {0x37, 192}, {0x50, 128}, {0x52, 128},
        {0x60, 64}, {0x61, 128}, {0x70, 64}, {0x75, 64}, {0x80, 64}, {0x86, 128}
    };

    void setup(AoC::Console& cc)
    {
        int deviceCount = 0;
        if (cudaGetDeviceCount(&deviceCount) != cudaSuccess)
            return;

        if (deviceCount == 0)
        {
            cc << "{r}ERROR: No compatible CUDA devices found!{d}" << endl;
            return;
        }

        cudaSetDevice(0);
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, 0);
        cc << "Using CUDA Device {g}" << deviceProp.name << "{d}" << endl;

        int driverVersion = 0, runtimeVersion = 0;
        cudaDriverGetVersion(&driverVersion);
        cudaRuntimeGetVersion(&runtimeVersion);
        if (driverVersion != runtimeVersion)
        {
            cc << "{y}Warning:{d} CUDA Driver Version = {g}" << driverVersion / 1000 << "." << (driverVersion % 100) / 10 <<
                "{d}, Runtime Version = {g}" << runtimeVersion / 1000 << "." << (runtimeVersion % 100) / 10 << "{d}" << endl;
        }

        int architecture = (deviceProp.major << 4) + deviceProp.minor;
        const auto& it = archCores.find(architecture);
        if (it == archCores.end())
        {
            cc << "{r}ERROR: CUDA Architecture " << deviceProp.major << "." << deviceProp.minor << " is not supported{d}" << endl;
            return;
        }
        
        mp = deviceProp.multiProcessorCount;
        cores_mp = it->second;
        cores_total = mp * cores_mp;
    }
}
