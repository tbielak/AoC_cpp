#include "2022_21.h"

namespace Day21_2022
{
	Equation::Equation(const string& s)
	{
		if (s[6] <= '9')
		{
			op = '=';
			value = stoll(s.substr(6));
		}
		else
		{
			op = s[11];
			src1 = s.substr(6, 4);
			src2 = s.substr(13);
			value = 0;
		}
	}

	Node::Node(Node* parent /* = 0 */)
	:	op('?'), parent(parent), left(0), right(0), human_to_the_left(false), value(-1)
	{
	}

	Node::~Node()
	{
		delete left;
		delete right;
	}

	void Main::build_tree(Node* me, const std::string& name, const map<string, Equation>& equations)
	{
		me->name = name;
		const Equation& eq = equations.find(name)->second;
		me->op = eq.op;
		if (eq.op == '=')
		{
			me->value = eq.value;
			return;
		}

		me->left = new Node(me);
		me->right = new Node(me);
		build_tree(me->left, eq.src1, equations);
		build_tree(me->right, eq.src2, equations);
	}

	Node* Main::load(const vector<string>& input)
	{
		map<string, Equation> equations;
		for (const string& s : input)
			equations.insert(map<string, Equation>::value_type(s.substr(0, 4), Equation(s)));

		Node* root = new Node();
		build_tree(root, "root", equations);
		return root;
	}

	int64_t Main::compute(Node* me)
	{
		switch (me->op)
		{
			case '+': return compute(me->left) + compute(me->right);
			case '-': return compute(me->left) - compute(me->right);
			case '*': return compute(me->left) * compute(me->right);
			case '/': return compute(me->left) / compute(me->right);
			default: return me->value;
		}
	}

	Node* Main::find_human(Node* me)
	{
		if (me->name == "humn")
			return me;

		Node* result = 0;
		if (me->left)
			result = find_human(me->left);
		
		if (result == 0 && me->right)
			result = find_human(me->right);

		return result;
	}

	void Main::mark_human_path(Node* me)
	{
		while (me->parent != 0)
		{
			me->parent->human_to_the_left = me->parent->left == me;
			me = me->parent;
		}
	}

	int64_t Main::find_human_value(Node* me)
	{
		while (1)
		{
			if (me->name == "humn")
				return me->value;

			int64_t value = me->human_to_the_left ? compute(me->right) : compute(me->left);
			switch (me->op)
			{
				case '+': value = me->value - value; break;
				case '-': value = me->human_to_the_left ? value + me->value : value - me->value; break;
				case '*': value = me->value / value; break;
				case '/': value = me->human_to_the_left ? value * me->value : value / me->value; break;
				default: break;	// do nothing at root node ('?')
			}

			if (me->human_to_the_left)
				me->left->value = value;
			else
				me->right->value = value;

			me = me->human_to_the_left ? me->left : me->right;
		}

		return -1;	// unreachable
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		Node* root = load(input);
		auto result = compute(root);
		delete root;
		return result;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		Node* root = load(input);
		Node* human = find_human(root);
		mark_human_path(human);

		root->op = '?';
		auto result = find_human_value(root);
		delete root;
		return result;
	}
}
