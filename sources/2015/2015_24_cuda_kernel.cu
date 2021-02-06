// puzzle input is kept in CUDA device constant memory
// maximum input length is defined here
__constant__ int day_24_2015_CUDA_input[32];

// CUDA device kernel code
__global__ void Day_24_2015_CUDA_findGroups_kernel(int groupsPerThread, unsigned char* results, int packages_count, int packages_weight)
{
    // thread index
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    // starting group
    int starting_group = idx * groupsPerThread;
    
    // check groups
    for (int g = 0; g < groupsPerThread; g++)
    {
        // check single group
        int group = starting_group + g;

        // find weight of the group and count number of packages in the group (bits set)
        int weight = 0;
        unsigned char number_of_packages = 0;
        for (int i = packages_count - 1; i >= 0; i--)
        {
            if (group & 1)
            {
                number_of_packages++;
                weight += day_24_2015_CUDA_input[i];
                if (weight > packages_weight)
                    break;
            }

            group >>= 1;
        }

        if (weight != packages_weight)
            number_of_packages = 0xff;      // perfect weight not found

        // perfect weight found -> store number of packages of the group
        results[starting_group + g] = number_of_packages;
    }
}

// CUDA device kernel code
__global__ void Day_24_2015_CUDA_findGroupsMin_kernel(int groupsPerThread, unsigned char* results, unsigned char* aggregated)
{
    // thread index
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    // starting group
    int starting_group = idx * groupsPerThread;

    // find minimum number of packages in the group
    unsigned char number_of_packages = 0xff;
    for (int g = 0; g < groupsPerThread; g++)
        if (number_of_packages > results[starting_group + g])
            number_of_packages = results[starting_group + g];

    aggregated[idx] = number_of_packages;
}

// CUDA device kernel code
__global__ void Day_24_2015_CUDA_findQEMin_kernel(int groupsPerThread, unsigned char* results, long long* minQE_results, int packages_count, unsigned char minimum_packages_count)
{
    // result
    long long minQE = 0x7fffffffffffffff;

    // thread index
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    // starting group
    int starting_group = idx * groupsPerThread;

    // check groups
    for (int g = 0; g < groupsPerThread; g++)
    {
        // check single group
        int group = starting_group + g;

        // check if group has requested number of packages
        if (results[group] != minimum_packages_count)
            continue;

        // calculate QE
        long long v = 1;
        for (int i = packages_count - 1; i >= 0; i--)
        {
            if (group & 1)
                v *= day_24_2015_CUDA_input[i];

            group >>= 1;
        }

        // is it minQE so far?
        if (minQE > v) 
            minQE = v;
    }

    // return minQE of groupsPerThread groups
    minQE_results[idx] = minQE;
}

// host code: storing input in device constant memory
bool Day_04_2015_CUDA_input(const int input[32])
{
    return cudaMemcpyToSymbol(day_24_2015_CUDA_input, input, 4 * 32) == cudaSuccess;
}

// host code: calling CUDA device kernel code
bool Day_24_2015_CUDA_findGroups(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, int packages_count, int packages_weight)
{
    Day_24_2015_CUDA_findGroups_kernel << <blocksPerGrid, threadsPerBlock >> > (groupsPerThread, results, packages_count, packages_weight);
    bool status = (cudaGetLastError() == cudaSuccess);
    
    cudaDeviceSynchronize();
    return status;
}

// host code: calling CUDA device kernel code
bool Day_24_2015_CUDA_findGroupsMin(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, unsigned char* aggregated)
{
    Day_24_2015_CUDA_findGroupsMin_kernel << <blocksPerGrid, threadsPerBlock >> > (groupsPerThread, results, aggregated);
    bool status = (cudaGetLastError() == cudaSuccess);

    cudaDeviceSynchronize();
    return status;
}

// host code: calling CUDA device kernel code
bool Day_24_2015_CUDA_findQEMin(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, long long* minQE_results, int packages_count, unsigned char minimum_packages_count)
{
    Day_24_2015_CUDA_findQEMin_kernel << <blocksPerGrid, threadsPerBlock >> > (groupsPerThread, results, minQE_results, packages_count, minimum_packages_count);
    bool status = (cudaGetLastError() == cudaSuccess);

    cudaDeviceSynchronize();
    return status;
}
