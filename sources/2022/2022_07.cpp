#include "2022_07.h"

namespace Day07_2022
{
	Directory::Directory(Directory* parent /* = 0 */)
	:	_size(0), _parent(parent)
	{
	}

	void Directory::scan_terminal_output(const vector<string>& input)
	{
		Directory* root = this;
		Directory* current = root;
		for (const string& s : input)
		{
			if (s == "$ ls")
				continue;

			if (s.substr(0, 4) == "$ cd")
			{
				string name = s.substr(5);
				if (name == "/")
					current = root;
				else
					current = (name == "..") ? current->_parent : current->_dirs.find(name)->second;
			}
			else
				if (s.substr(0, 3) == "dir")
					current->_dirs[s.substr(4)] = new Directory(current);
				else
					current->_file_sizes.push_back(stol(s));
		}
	}

	size_t Directory::update_dir_sizes()
	{
		_size = reduce(_file_sizes.begin(), _file_sizes.end());

		for (auto& it : _dirs)
			_size += it.second->update_dir_sizes();

		return _size;
	}

	Directory* Directory::load(const vector<string>& input)
	{
		Directory* root = new Directory();
		root->scan_terminal_output(input);
		root->update_dir_sizes();
		return root;
	}

	size_t Directory::size() const
	{
		return _size;
	}

	void Directory::sum_sizes_up_to(size_t limit, size_t& result) const
	{
		if (_size <= limit)
			result += _size;

		for (const auto& it : _dirs)
			it.second->sum_sizes_up_to(limit, result);
	}

	void Directory::min_size_to_delete(size_t needed_space, size_t& result) const
	{
		if (_size >= needed_space)
			result = min(_size, result);

		for (const auto& it : _dirs)
			it.second->min_size_to_delete(needed_space, result);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		size_t size = 0;
		Directory::load(input)->sum_sizes_up_to(100000, size);
		return size;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		Directory* root = Directory::load(input);
		const size_t total_space = 70000000;
		size_t space_used = root->size();
		size_t free_space = total_space - space_used;
		size_t needed_space = 30000000 - free_space;
		size_t min_dir_size = total_space;
		root->min_size_to_delete(needed_space, min_dir_size);
		return min_dir_size;
	}
}
