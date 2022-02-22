#include "2017_08.h"

namespace Day08_2017
{
	Instruction::Instruction(const string& input)
	{
		smatch matches;
		regex regex("([a-z]*) (inc|dec) ([-0-9]*) if ([a-z]*) ([<>=!]*) ([-0-9]*)");
		regex_search(input, matches, regex);
		dst = matches[1];
		cmp = matches[4];
		int sign = matches[2] == "inc" ? 1 : -1;
		dst_value = stoi(matches[3]) * sign;
		cmp_value = stoi(matches[6]);

		string op = matches[5];
		if (op == "<") comparator = [](int a, int b) { return a < b; };
		else if (op == ">") comparator = [](int a, int b) { return a > b; };
		else if (op == "<=") comparator = [](int a, int b) { return a <= b; };
		else if (op == ">=") comparator = [](int a, int b) { return a >= b; };
		else if (op == "==") comparator = [](int a, int b) { return a == b; };
		else if (op == "!=") comparator = [](int a, int b) { return a != b; };
	}

	void Instruction::execute(t_regs& regs, int& highest_value) const
	{
		if (comparator(regs[cmp], cmp_value))
			regs[dst] += dst_value;

		highest_value = max(highest_value, regs[dst]);
	}

	t_vecIns Main::load(const vector<string>& input)
	{
		t_vecIns instructions;
		for (const auto& line : input)
			instructions.push_back(Instruction(line));

		return instructions;
	}

	pair<t_regs, int> Main::execute(const t_vecIns& instructions)
	{
		t_regs regs;
		int highest_value = INT_MIN;
		for (const auto& ins : instructions)
			ins.execute(regs, highest_value);

		return make_pair(regs, highest_value);
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		auto instructions = load(input);
		auto [regs, highest_value] = execute(instructions);

		return make_pair(max_element(regs.begin(), regs.end(),
			[](const auto& a, const auto& b) -> int { return a.second < b.second; })->second,
			highest_value);
	}
}
