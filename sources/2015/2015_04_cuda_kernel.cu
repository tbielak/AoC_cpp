// puzzle input is kept in CUDA device constant memory
// maximum input length is defined here
__constant__ char day_04_2015_CUDA_input[16];

// real input length
__constant__ int day_04_2015_CUDA_input_length;

// below: including single-MD5-transform routine shared by two CPU solutions and one GPU solution
// note: GPU version requires prefix __device__ placing the code on GPU side
#define PREFIX_2015_04 __device__
#define FNAME_2015_04 Day_04_2015_CUDA_md5_single_transform
#include "2015_04_shared.h"

// CUDA device kernel code
__global__ void Day_04_2015_CUDA_md5Check_kernel(unsigned char* results, unsigned int result_mask, int starting_point)
{
	// prepare 64-byte buffer with input
    char buffer[64];

    // copy puzzle input
    int i = 0;
    for (; i < day_04_2015_CUDA_input_length; i++)
        buffer[i] = day_04_2015_CUDA_input[i];
    
    // add appropriate number basing on thread index
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
	int number = starting_point + idx;

    int j = i;
    while (number > 0)
    {
        for (int k = i; k > j; k--)
            buffer[k] = buffer[k - 1];

        buffer[j] = (number % 10) + '0';
        number /= 10;
        i++;
    }

    // MD5 padding with length
    int length = i * 8;
    if (i < 64)
        buffer[i++] = -128;

    for (; i < 64; i++)
        buffer[i] = 0;

    *((int*)(&buffer[56])) = length;

    // do single MD5 transform and take part of the digest
    unsigned int result = FNAME_2015_04((unsigned int*)buffer);

    // check requested number of zeros and store result
    results[idx] = ((result & result_mask) == result) ? 1 : 0;
}

// host code: storing input in device constant memory
bool Day_04_2015_CUDA_input(const char* input, int input_length)
{
    if (cudaMemcpyToSymbol(day_04_2015_CUDA_input, input, input_length) != cudaSuccess)
        return false;
    
    if (cudaMemcpyToSymbol(day_04_2015_CUDA_input_length, &input_length, 4) != cudaSuccess)
        return false;

    return true;
}

// host code: calling CUDA device kernel code
bool Day_04_2015_CUDA_md5Check(int blocksPerGrid, int threadsPerBlock, unsigned char* results, unsigned int result_mask, int starting_point)
{
	Day_04_2015_CUDA_md5Check_kernel << <blocksPerGrid, threadsPerBlock >> > (results, result_mask, starting_point);
	return (cudaGetLastError() == cudaSuccess);
}

// undefine macros (different definitions for CPU/GPU version)
#undef PREFIX_2015_04
#undef FNAME_2015_04
