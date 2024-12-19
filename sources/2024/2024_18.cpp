#include "2024_18.h"

namespace Day18_2024
{
	Position::Position(int x, int y)
	:	x(x), y(y)
	{
	}

	Position::Position(const string& s)
	{
		size_t pos = s.find_first_of(',');
		x = stoi(s.substr(0, pos));
		y = stoi(s.substr(pos + 1));
	}

	bool Position::operator < (const Position& rhs) const
	{
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	bool Position::operator == (const Position& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	string Position::to_string() const
	{
		return std::to_string(x) + "," + std::to_string(y);
	}

	vector<Position> Main::load(const vector<string>& input)
	{
		vector<Position> positions;
		for (const string& s : input)
			positions.push_back(Position(s));

		return positions;
	}

	int Main::steps(size_t count, const vector<Position>& input, const Position& start, const Position& end)
	{
		set<Position> positions;
		for (size_t i = 0; i < count; i++)
			positions.insert(input[i]);

		set<Position> visited;
		queue<pair<Position, int>> q;
		q.push(make_pair(start, 0));

		vector<int> move_x = { 1, 0, -1, 0 };
		vector<int> move_y = { 0, 1, 0, -1 };

		while (q.size() > 0)
		{
			auto [pos, distance] = q.front();
			q.pop();

			if (pos == end)
				return distance;

			for (int i = 0; i < 4; i++)
			{
				Position npos(pos.x + move_x[i], pos.y + move_y[i]);
				if (npos.x < 0 || npos.x > end.x || npos.y < 0 || npos.y > end.y)
					continue;

				if (positions.find(npos) != positions.end())
					continue;

				if (visited.find(npos) != visited.end())
					continue;

				visited.insert(npos);
				q.push(make_pair(npos, distance + 1));
			}
		}

		return 0;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto positions = load(input);
		return steps(1024, positions, Position(0, 0), Position(70, 70));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto positions = load(input);
		int left = 1024;
		int right = (int)positions.size();
		while (left < right - 1)
		{
			int middle = (left + right) / 2;
			if (steps(middle, positions, Position(0, 0), Position(70, 70)) == 0)
				right = middle - 1;
			else
				left = middle;
		}

		return positions[left].to_string();
	}
}
