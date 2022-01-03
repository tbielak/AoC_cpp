#include "2016_09.h"

namespace Day09_2016
{
	intmax_t decompressed_length(const string& input, size_t begin_index, size_t end_index, bool recursive)
	{
		intmax_t len = end_index - begin_index;
		for (size_t i = begin_index; i < end_index; i++)
			if (input[i] == '(')
			{
				size_t pos = input.find_first_of(')', i);
				string inside = input.substr(i + 1, pos - i - 1);

				smatch matches;
				regex regex("([0-9]*)x([0-9]*)");
				regex_search(inside, matches, regex);

				int substring_length = stoi(matches[1]);
				int substring_count = stoi(matches[2]);
				
				// remove compressed part
				len -= (pos - i + 1 + substring_length);

				// add decompressed part
				if (recursive)
					len += decompressed_length(input, pos + 1, pos + 1 + substring_length, true) * substring_count;
				else
					len += substring_length * substring_count;

				// move to next part
				i = pos + substring_length;
			}

		return len;
	}

	intmax_t part_one(const string& input)
	{
		return decompressed_length(input, 0, input.size(), false);
	}

	intmax_t part_two(const string& input)
	{
		return decompressed_length(input, 0, input.size(), true);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input[0]);
		auto p2 = part_two(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
