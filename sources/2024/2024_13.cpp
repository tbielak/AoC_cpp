#include "2024_13.h"

namespace Day13_2024
{
	Point::Point()
	:	x(-1), y(-1)
	{
	}

	Point::Point(const string& input, const string& rs)
	{
		smatch matches;
		regex regex(rs);
		regex_search(input, matches, regex);
		x = stoll(matches[1]);
		y = stoll(matches[2]);
	}

	Machine::Machine(const string& a, const string& b, const string& p, int64_t add)
	{
		_a = Point(a, "Button A: X\\+([0-9]+), Y\\+([0-9]+)");
		_b = Point(b, "Button B: X\\+([0-9]+), Y\\+([0-9]+)");
		_prize = Point(p, "Prize: X=([0-9]+), Y=([0-9]+)");
		_prize.x += add;
		_prize.y += add;
	}

	int64_t Machine::play() const
	{
		int64_t W = _a.x * _b.y - _a.y * _b.x;
		int64_t Wx = _prize.x * _b.y - _prize.y * _b.x;
		int64_t Wy = _a.x * _prize.y - _a.y * _prize.x;
		if (W == 0)
			return 0;

		int64_t pa = Wx / W;
		int64_t pb = Wy / W;
		return (pa * _a.x + pb * _b.x == _prize.x && pa * _a.y + pb * _b.y == _prize.y) ? pa * 3 + pb : 0;
	}

	vector<Machine> Main::load(const vector<string>& input, int64_t add)
	{
		vector<Machine> m;
		for (size_t i = 0; i < input.size(); i += 4)
			m.push_back(Machine(input[i], input[i + 1], input[i + 2], add));

		return m;
	}

	int64_t Main::solve(const vector<string>& input, int64_t add /* = 0 */)
	{
		int64_t tokens = 0;
		for (const auto& m : load(input, add))
			tokens += m.play();

		return tokens;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 10000000000000LL);
	}
}
