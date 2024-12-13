#include "2024_09.h"

namespace Day09_2024
{
	AoC::Output Main::part_one(const string& input)
	{
		// ids of files: on the left side and on the right side of the map
		size_t lid = 0;
		size_t rid = 0;	// correct value will be assigned later

		// pointers to the files in the map (left, right)
		const char* lptr = input.data();
		const char* rptr = input.data() + input.size() - 1;

		// length of the file at the end
		size_t rlen = 0;

		// current block number
		size_t block = 0;

		// total number of blocks (taken by all files)
		size_t total_blocks = 0;
		for (size_t i = 0; i < input.size(); i++)
			total_blocks += input[i++] - '0';

		// checksum, computed on the fly, no need to move anything in part one :-)
		int64_t checksum = 0;
		while (1)
		{
			// file from the left side
			size_t block_count = *lptr++ - '0';
			for (size_t i = 0; i < block_count; i++)
			{
				// update checksum, check if done
				checksum += block++ * lid;
				if (block == total_blocks)
					return checksum;
			}

			// free space from the left side
			block_count = *lptr++ - '0';
			while (block_count > 0)
			{
				if (rlen == 0)
				{
					// length of file from the right side
					rlen = *rptr - '0';
					rid = (rptr - input.data()) / 2;

					// previous file on right side
					rptr -= 2;
				}

				// update checksum, check if done
				checksum += block++ * rid;
				if (block == total_blocks)
					return checksum;

				// decrease len and block count
				rlen--;
				block_count--;
			}

			// next file from the left side
			lid++;
		}
	}

	AoC::Output Main::part_two(const string& input)
	{
		// disk map
		t_diskmap map;

		// starting positions of files (blocks to move)
		set<int> to_move;

		// load input
		int pos = 0;
		int id = 0;
		for (size_t i = 0; i < input.size(); i++)
		{
			int length = input[i] - '0';
			map[pos] = BlockInfo({ length, i & 1 ? -1 : id++ });
			if ((i & 1) == 0)
				to_move.insert(pos);

			pos += length;
		}

		// move files
		for (auto pos = to_move.rbegin(); pos != to_move.rend(); pos++)
			move_file(map, *pos);

		// calculate checksum
		int64_t checksum = 0;
		for (const auto& [pos, info] : map)
			if (info.id > -1)
				for (int i = 0; i < info.length; i++)
					checksum += (pos + i) * info.id;
		
		return checksum;
	}

	// move file starting at pos
	void Main::move_file(t_diskmap& map, int pos)
	{
		// find file
		auto src = map.find(pos);

		// try to place it as close to the beginning of the disk as possible
		for (auto dst = map.begin(); dst->first < src->first; dst++)
		{
			// if found free block and file fits there...
			if (dst->second.id == -1 && dst->second.length >= src->second.length)
			{
				// ...move the file in three easy steps:
				// 1) check if after moving there are some free blocks left
				int free_blocks_left = dst->second.length - src->second.length;

				// 2) move file
				dst->second = src->second;
				src->second.id = -1;

				// 3) if any free blocks left insert appropriate info into the map
				if (free_blocks_left > 0)
					map[dst->first + dst->second.length] = BlockInfo({ free_blocks_left, -1 });

				// moving done
				return;
			}
		}
	}
}
