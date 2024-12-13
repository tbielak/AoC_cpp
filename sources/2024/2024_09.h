#ifndef __2024_09__
#define __2024_09__

#include "../shared/Solution.h"

namespace Day09_2024
{
	class BlockInfo
	{
	public:
		int length;		// length in blocks
		int id;			// id of file (or -1 if free space)
	};

	typedef map<int, BlockInfo> t_diskmap;	// map: block starting position to block info

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static void move_file(t_diskmap& map, int pos);
	};
}

#endif
