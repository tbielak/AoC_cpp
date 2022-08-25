#include "2018_12.h"

namespace Day12_2018
{
	Solver::Solver(const vector<string>& input)
	{
		_state = input[0].substr(input[0].find(':') + 2);

		for (size_t i = 2; i < input.size(); i++)
			_notes[input[i].substr(0, 5)] = input[i][9];
	}

	int64_t Solver::count(int generations)
	{
		int first_pot = 0;
		for (int j = 0; j < generations; j++)
		{
			first_pot -= 3;
			_state = "..." + _state + "...";

			string dst = _state;
			for (int i = 0; i < (int)_state.size() - 4; i++)
				dst[i + 2] = _notes.find(_state.substr(i, 5))->second;

			_state = move(dst);
		}

		int count = 0;
		for (int i = 0; i < (int)_state.size(); i++)
			if (_state[i] == '#')
				count += i + first_pot;

		return count;
	}

	int64_t Solver::smart_count(int64_t generations)
	{
		int count = 0;
		int first_pot = 0;
		string prev;
		int prev_idx = 0;
		for (int gen = 0; ; gen++)
		{
			first_pot -= 3;
			_state = "..." + _state + "...";

			string dst = _state;
			for (int i = 0; i < (int)_state.size() - 4; i++)
				dst[i + 2] = _notes.find(_state.substr(i, 5))->second;

			_state = move(dst);

			size_t pos_l = _state.find_first_of('#');
			size_t pos_r = _state.find_last_of('#');
			string s = _state.substr(pos_l, pos_r - pos_l + 1);
			if (prev == s)
			{
				if (count == 100)
				{
					int offs = first_pot + (int)pos_l;
					int diff = offs - prev_idx;

					int64_t x = (offs - 1) + (generations - gen) * diff;

					int64_t count = 0;
					for (int i = 0; i < (int)s.size(); i++)
						if (s[i] == '#')
							count += i + x;

					return count;
				}
				else
					count++;
			}

			prev = s;
			prev_idx = first_pot + (int)pos_l;
		}

		return -1;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver(input).count(20);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Solver(input).smart_count(50000000000);
	}
}
