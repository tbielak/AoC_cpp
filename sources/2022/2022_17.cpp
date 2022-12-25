#include "2022_17.h"

namespace Day17_2022
{
	vector<vector<string>> Tetris::_rocks = { {"@@@@"}, {".@.", "@@@", ".@."} , {"..@", "..@", "@@@"} , {"@", "@", "@", "@"} , {"@@", "@@"} };

	Tetris::Tetris(const string& jet_pattern)
	:	_rock_idx(0), _jet_idx(0), _jet_pattern(jet_pattern), _chamber({ "+-------+" }), _height(0), _skipped(0)
	{
	}

	int64_t Tetris::run(int64_t count)
	{
		map<string, pair<int64_t, size_t>> cache;
		while (count > 0)
		{
			string key;
			for (const string& c : _chamber)
				key += c.substr(1, 7);

			const auto& it = cache.find(key);
			if (it == cache.end())
			{
				cache[key] = make_pair(count, _height);
				drop_rock();
				count--;
			}
			else
			{
				size_t cycle_height = _height - it->second.second;
				int64_t cycle_count = it->second.first - count;
				_skipped += (count / cycle_count) * cycle_height;
				count %= cycle_count;
				break;
			}
		}

		while (count > 0)
		{
			drop_rock();
			count--;
		}

		return _height + _skipped;
	}

	void Tetris::put_next_rock()
	{
		_height += 3 + _rocks[_rock_idx].size();
		for (size_t i = 0; i < 3 + _rocks[_rock_idx].size(); i++)
			_chamber.insert(_chamber.begin(), "|.......|");

		for (size_t i = 0; i < _rocks[_rock_idx].size(); i++)
			for (size_t j = 0; j < _rocks[_rock_idx][0].size(); j++)
				_chamber[i][j + 3] = _rocks[_rock_idx][i][j];

		_rock_idx++;
		_rock_idx %= _rocks.size();
	}

	int Tetris::rock_line() const
	{
		int start = 0;
		while (_chamber[start].find_first_of('@') == string::npos)
			start++;

		return start;
	}

	int Tetris::pushing_direction()
	{
		char jet = _jet_pattern[_jet_idx++];
		_jet_idx %= _jet_pattern.size();
		return jet == '<' ? -1 : 1;
	}

	void Tetris::try_to_push(int start, int direction)
	{
		bool move = true;
		for (int i = start; ; i++)
		{
			size_t pos = direction < 0 ? _chamber[i].find_first_of('@') : _chamber[i].find_last_of('@');
			if (pos == string::npos)
				break;

			if (_chamber[i][pos + direction] != '.')
				move = false;
		}

		if (move)
		{
			for (int i = start; ; i++)
			{
				size_t pos = direction < 0 ? _chamber[i].find_first_of('@') : _chamber[i].find_last_of('@');
				if (pos == string::npos)
					break;

				_chamber[i][pos + direction] = '@';
				while (_chamber[i][pos] == '@') pos -= direction;
				_chamber[i][pos + direction] = '.';
			}
		}
	}

	int Tetris::fall_possible(int i) const
	{
		for (; ; i++)
		{
			if (_chamber[i].find_first_of('@') == string::npos)
				break;

			for (int j = 1; j <= 7; j++)
				if (_chamber[i][j] == '@' && _chamber[i + 1][j] != '@' && _chamber[i + 1][j] != '.')
					return -1;
		}

		return i;
	}

	void Tetris::fall(int i)
	{
		for (; i > 0; i--)
			for (int j = 1; j <= 7; j++)
				if (_chamber[i - 1][j] == '@')
				{
					_chamber[i - 1][j] = '.';
					_chamber[i][j] = '@';
				}
	}

	void Tetris::remove_empty_rows()
	{
		while (_chamber[0] == "|.......|")
		{
			_chamber.erase(_chamber.begin());
			_height--;
		}
	}

	void Tetris::settle_down(int start)
	{
		for (int i = start; ; i++)
		{
			if (_chamber[i].find_first_of('@') == string::npos)
				break;

			for (int j = 1; j <= 7; j++)
				if (_chamber[i][j] == '@')
					_chamber[i][j] = '#';
		}
	}

	void Tetris::shorten_chamber(int maxlines)
	{
		while ((int)_chamber.size() > maxlines)
			_chamber.pop_back();
	}

	void Tetris::drop_rock()
	{
		put_next_rock();

		while (1)
		{
			int start = rock_line();
			try_to_push(start, pushing_direction());

			int i = fall_possible(start);
			if (i > -1)
			{
				fall(i);
				remove_empty_rows();
			}
			else
			{
				settle_down(start);
				break;
			}

			shorten_chamber(50);
		}
	}

	AoC::Output Main::part_one(const string& input)
	{
		return Tetris(input).run(2022);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return Tetris(input).run(1000000000000);
	}
}
