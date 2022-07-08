#include "2018_08.h"

namespace Day08_2018
{
	void Node::load(stringstream& ss)
	{
		int children_count;
		int metadata_count;
		ss >> children_count;
		ss >> metadata_count;

		children = vector<Node>(children_count);
		for (int i = 0; i < children_count; i++)
			children[i].load(ss);

		for (int i = 0; i < metadata_count; i++)
		{
			int m;
			ss >> m;
			metadata.push_back(m);
		}
	}

	int Node::recursive_sum_metadata() const
	{
		int sum = 0;
		for (auto x : metadata)
			sum += x;

		for (const Node& c : children)
			sum += c.recursive_sum_metadata();

		return sum;
	}

	int Node::value() const
	{
		int v = 0;
		if (children.size() == 0)
			for (auto m : metadata)
				v += m;
		else
			for (auto m : metadata)
				if (m - 1 < (int)children.size())
					v += children[m - 1].value();

		return v;
	}

	Node Main::load(const string& input)
	{
		Node root;
		stringstream ss(input);
		root.load(ss);
		return root;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return load(input).recursive_sum_metadata();
	}

	AoC::Output Main::part_two(const string& input)
	{
		return load(input).value();
	}
}
