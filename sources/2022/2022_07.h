#ifndef __2022_07__
#define __2022_07__

#include "../shared/Solution.h"

namespace Day07_2022
{
	class Directory
	{
	public:
		Directory(Directory* parent = 0);
		static Directory* load(const vector<string>& input);

		size_t size() const;
		void sum_sizes_up_to(size_t limit, size_t& result) const;
		void min_size_to_delete(size_t needed_space, size_t& result) const;

	private:
		size_t _size;
		Directory* _parent;
		map<string, Directory*> _dirs;
		vector<size_t> _file_sizes;
		
		void scan_terminal_output(const vector<string>& input);
		size_t update_dir_sizes();
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
