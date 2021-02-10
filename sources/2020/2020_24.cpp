#include "2020_24.h"

namespace Day24_2020
{
	Lobby::Lobby(const vector<string>& input)
	:	_width(-1), _height(-1)
	{
		_xmin = 0;
		_xmax = 0;
		_ymin = 0;
		_ymax = 0;
		for (const auto& s : input)
		{
			int x = 0;
			int y = 0;
			for (size_t i = 0; i < s.size(); i++)
			{
				int v = 2;
				if (s[i] == 's') { v--; y++; i++; }
				if (s[i] == 'n') { v--; y--; i++; }
				if (s[i] == 'e') x += v; else x -= v;
			}

			t_point p(x, y);
			_xmin = min(_xmin, x);
			_xmax = max(_xmax, x);
			_ymin = min(_ymin, y);
			_ymax = max(_ymax, y);

			const auto& it = _blacks.find(p);
			if (it == _blacks.end())
				_blacks.insert(p);
			else
				_blacks.erase(it);
		}
	}

	size_t Lobby::count_blacks() const
	{
		return _blacks.size();
	}

	void Lobby::create_floor()
	{
		// construct larger floor
		_width = _xmax - _xmin + 9;
		_height = _ymax - _ymin + 5;
		int cx = _width / 2;
		int cy = _height / 2;

		vector<bool> v(_width, true);
		_floor = vector<vector<bool>>(_height, v);
		for (const auto& p : _blacks)
			_floor[p.second + cy][p.first + cx] = false;
	}

	void Lobby::living_art()
	{
		// inflate living floor
		vector<bool> v(_width + 4, true);
		vector<vector<bool>> tmp = vector<vector<bool>>(_height + 2, v);
		for (int y = 1; y < _height - 1; y++)
			for (int x = 2; x < _width - 2; x++)
				tmp[y + 1][x + 2] = _floor[y][x];

		// flip tiles
		for (int y = 1; y < _height - 1; y++)
			for (int x = 2; x < _width - 2; x++)
			{
				int cnt = adjacent(y, x);
				if (!_floor[y][x] && (cnt == 0 || cnt > 2)) tmp[y + 1][x + 2] = true;
				if (_floor[y][x] && cnt == 2) tmp[y + 1][x + 2] = false;
			}

		// make it current one
		_floor = move(tmp);
		_width += 4;
		_height += 2;
	}

	int Lobby::adjacent(int y, int x) const
	{
		const vector<pair<int, int>> neighbours = { {-2, 0}, {2, 0}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };

		int cnt = 0;
		for (int i = 0; i < 6; i++)
			if (!_floor[y + neighbours[i].second][x + neighbours[i].first])
				cnt++;

		return cnt;
	}

	size_t Lobby::count_blacks_on_the_floor() const
	{
		size_t cnt = 0;
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				if (!_floor[y][x])
					cnt++;

		return cnt;
	}

	size_t part_one(Lobby& lobby)
	{
		return lobby.count_blacks();
	}

	size_t part_two(Lobby& lobby)
	{
		lobby.create_floor();
		for (int i = 0; i < 100; i++)
			lobby.living_art();

		return lobby.count_blacks_on_the_floor();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		Lobby lobby(input);
		auto p1 = part_one(lobby);
		auto p2 = part_two(lobby);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
