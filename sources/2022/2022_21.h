#ifndef __2022_21__
#define __2022_21__

#include "../shared/Solution.h"

namespace Day21_2022
{
	class Equation
	{
	public:
		Equation(const string& s);

		string src1;
		string src2;
		char op;
		int64_t value;
	};

	class Node
	{
	public:
		Node(Node* parent = 0);
		~Node();

		string name;
		char op;
		Node* parent;
		Node* left;
		Node* right;
		bool human_to_the_left;
		int64_t value;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void build_tree(Node* me, const std::string& name, const map<string, Equation>& equations);
		static Node* load(const vector<string>& input);
		static int64_t compute(Node* me);
		static Node* find_human(Node* me);
		static void mark_human_path(Node* me);
		static int64_t find_human_value(Node* me);
	};
}

#endif
