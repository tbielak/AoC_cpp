#include "2024_21.h"

namespace Day21_2024
{
	Position::Position(int row /* = 0 */, int col /* = 0 */)
	:	row(row), col(col)
	{
	}

	bool Position::operator < (const Position& rhs) const
	{
		return row == rhs.row ? col < rhs.col : row < rhs.row;
	}

	bool Position::operator == (const Position& rhs) const
	{
		return row == rhs.row && col == rhs.col;
	}

	Solver::Solver()
	{
		_numeric_keypad = create_keypad({ "789", "456", "123", " 0A" }, _valid_numeric_positions);
		_directional_keypad = create_keypad({ " ^A", "<v>" }, _valid_directional_positions);
	}

	int64_t Solver::go(const vector<string>& input, int target_depth)
	{
		_target_depth = target_depth;

		int64_t result = 0;
		for (const string& s : input)
		{
			int64_t len = 0;
			char cur = 'A';
			for (char t : s)
			{
				len += go(cur, t, 0);
				cur = t;
			}

			result += stoll(s.substr(0, 3)) * len;
		}

		return result;
	}

	map<char, Position> Solver::create_keypad(const vector<string>& layout, set<Position>& valid)
	{
		map<char, Position> keypad;
		for (int row = 0; row < (int)layout.size(); row++)
			for (int col = 0; col < (int)layout[row].size(); col++)
				if (layout[row][col] != ' ')
				{
					valid.insert(Position(row, col));
					keypad[layout[row][col]] = Position(row, col);
				}

		return keypad;
	}

	vector<string> Solver::generate_reversed(const Position& start, const Position& end, const set<Position>& valid)
	{
		if (valid.find(start) == valid.end())
			return {};

		if (start == end)
			return { "A" };

		vector<string> ret;
		if (end.row < start.row)
			for (string s : generate_reversed(Position(start.row - 1, start.col), end, valid))
				ret.push_back(s + '^');

		if (end.row > start.row)
			for (string s : generate_reversed(Position(start.row + 1, start.col), end, valid))
				ret.push_back(s + 'v');

		if (end.col < start.col)
			for (string s : generate_reversed(Position(start.row, start.col - 1), end, valid))
				ret.push_back(s + '<');
				
		if (end.col > start.col)
			for (string s : generate_reversed(Position(start.row, start.col + 1), end, valid))
				ret.push_back(s + '>');
				
		return ret;
	}
	
	vector<string> Solver::generate(const Position& start, const Position& end, const set<Position>& valid)
	{
		vector<string> paths = generate_reversed(start, end, valid);
		for (auto& p : paths)
			reverse(p.begin(), p.end());

		return paths;
	}

	int64_t Solver::go(char start, char end, int depth)
	{
		if (depth == _target_depth)
			return 1;

		string key = string(1, start) + string(1, end) + to_string(depth);
		auto it = _cache.find(key);
		if (it != _cache.end())
			return it->second;

		auto paths = (depth == 0 ? generate(_numeric_keypad[start], _numeric_keypad[end], _valid_numeric_positions)
			: generate(_directional_keypad[start], _directional_keypad[end], _valid_directional_positions));

		int64_t best = LLONG_MAX;
		for (const string& p : paths)
		{
			int64_t len = 0;
			char cur = 'A';
			for (char t : p)
			{
				len += go(cur, t, depth + 1);
				cur = t;
			}
				
			best = min(best, len);
		}

		return _cache[key] = best;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver().go(input, 3);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Solver().go(input, 26);
	}
}
