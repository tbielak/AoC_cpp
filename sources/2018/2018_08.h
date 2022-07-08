#ifndef __2018_08__
#define __2018_08__

#include "../shared/Solution.h"

namespace Day08_2018
{
	class Node
	{
	public:
		vector<Node> children;
		vector<int> metadata;

		void load(stringstream& ss);
		int recursive_sum_metadata() const;
		int value() const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static Node load(const string& input);
	};
}

#endif
