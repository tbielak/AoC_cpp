#ifndef __2015_24_CUDA__
#define __2015_24_CUDA__

#include "../shared/input_output.h"

// Algortihm highlights:
//
// There are 28 packages of different weight on input.
// We can compose 2^28 different groups containing or not i-th package, i = [0..27].
// Each group number [0..2^28-1] is also the group configuration:
// i-th bit set indicates that the i-th package is included in the group and
// the weight of i-th package should be added to the weight of the group.
//
// The following CUDA routine copies input weights to device constant memory.
// (note: maximum nuber of packages is limited to 32)
//
extern bool Day_04_2015_CUDA_input(const int input[32]);

//
// The following CUDA routine starts (blocksPerGrid * threadsPerBlock) CUDA threads.
// Each thread sums weights of the packages in groupsPerThread groups.
// We are looking for the groups which weight == packages_weight. 
// When found the result is the number of packages in the group, 0xff otherwise.
// The result is stored in an appriopriate element of results array.
// i-th byte of results array is the result of i-th group.
// (note: this array is not copied to host memory, see next routine)
//
extern bool Day_24_2015_CUDA_findGroups(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, int packages_count, int packages_weight);

//
// The following CUDA routine aggregates results obtained from the previous routine.
// (blocksPerGrid * threadsPerBlock) CUDA threads are started, each thread finds minimum
// value of groupsPerThread groups from result array and places a single value in aggregated array.
// (note: aggregated array is then copied to host memory to find single minimum value of all groups)
//
extern bool Day_24_2015_CUDA_findGroupsMin(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, unsigned char* aggregated);

//
// The following CUDA routine finds the smallest quantum entanglement of groups with minimum_packages_count packages.
// (blocksPerGrid * threadsPerBlock) CUDA threads are started, each thread scans groupsPerThread groups and for each
// group which has minimum_packages_count, which is checked in results array, quantum entanglement is calculated.
// Then - minimum quantum entanglement of groupsPerThread groups is placed in minQE_results array.
// (note: this array is then copied to host memory to find the smallest quantum entanglement of all groups).
//
extern bool Day_24_2015_CUDA_findQEMin(int blocksPerGrid, int threadsPerBlock, int groupsPerThread, unsigned char* results, long long* minQE_results, int packages_count, unsigned char minimum_packages_count);

namespace Day24_2015_CUDA
{
	typedef vector<int> t_vecint;

	class QEEngine
	{
	public:
		QEEngine(const t_input& input);
		~QEEngine();

		bool init();
		intmax_t run(int split);

	private:
		t_vecint _input;
		int _threadsPerBlock;
		int _blocksPerGrid;
		int _groupsPerThread;
		unsigned char* _cuda_results;
		unsigned char* _cuda_aggregated;
		unsigned char* _host_aggregated;
		long long* _cuda_minQE;
		long long* _host_minQE;
	};

	t_output main(const t_input& input);
}

#endif
