#include "2020_20.h"

namespace Day20_2020
{
	Image::Image(const t_bitmap& bitmap)
	:	_bitmap(bitmap)
	{
		_n = bitmap.size();
	}

	int Image::top_edge()
	{
		return edge_as_int(_bitmap[0]);
	}

	int Image::right_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[i][_n - 1];

		return edge_as_int(s);
	}

	int Image::bottom_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[_n - 1][_n - i - 1];

		return edge_as_int(s);
	}

	int Image::left_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[_n - i - 1][0];

		return edge_as_int(s);
	}

	int Image::top_reversed_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[0][_n - i - 1];

		return edge_as_int(s);
	}

	int Image::right_reversed_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[_n - i - 1][_n - 1];

		return edge_as_int(s);
	}

	int Image::bottom_reversed_edge()
	{
		return edge_as_int(_bitmap[_n - 1]);
	}

	int Image::left_reversed_edge()
	{
		string s;
		for (size_t i = 0; i < _n; i++)
			s += _bitmap[i][0];

		return edge_as_int(s);
	}

	void Image::flip_horizontally()
	{
		for (size_t i = 0; i < _n / 2; i++)
			swap(_bitmap[i], _bitmap[_n - 1 - i]);
	}

	void Image::flip_vertically()
	{
		for (size_t i = 0; i < _n; i++)
			reverse(_bitmap[i].begin(), _bitmap[i].end());
	}

	void Image::rotate_clockwise()
	{
		string s(_n, '?');
		t_bitmap tmp = t_bitmap(_n, s);
		for (size_t i = 0; i < _n; i++)
			for (size_t j = 0; j < _n; j++)
				tmp[i][j] = _bitmap[_n - j - 1][i];

		_bitmap = move(tmp);
	}

	void Image::rotate_counterclockwise()
	{
		string s(_n, '?');
		t_bitmap tmp = t_bitmap(_n, s);
		for (size_t i = 0; i < _n; i++)
			for (size_t j = 0; j < _n; j++)
				tmp[_n - j - 1][i] = _bitmap[i][j];

		_bitmap = move(tmp);
	}

	void Image::release_monsters()
	{
		size_t max_y = _bitmap.size() - _monster_height;
		size_t max_x = _bitmap[0].size() - _monster_width;
		for (size_t y = 0; y < max_y; y++)
			for (size_t x = 0; x < max_x; x++)
				if (monster_fits_here(x, y))
					drop_monster(x, y);
	}

	bool Image::monster_fits_here(size_t x, size_t y)
	{
		for (const auto& p : _monster_shape)
			if (_bitmap[y + p.second][x + p.first] != '#')
				return false;

		return true;
	}

	void Image::drop_monster(size_t x, size_t y)
	{
		for (const auto& p : _monster_shape)
			_bitmap[y + p.second][x + p.first] = 'O';
	}

	int Image::count_hashes()
	{
		size_t c = 0;
		for (const auto& s : _bitmap)
			c += count(s.begin(), s.end(), '#');

		return (int)c;
	}

	int Image::edge_as_int(const string& s)
	{
		int v = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			v <<= 1;
			if (s[i] == '#')
				v |= 1;
		}

		return v;
	}

	Tile::Tile(const string& header, const t_bitmap& bitmap)
	:	_image(bitmap)
	{
		size_t p1 = header.find(' ');
		size_t p2 = header.find(':');
		_id = stoi(header.substr(p1, p2 - p1));
		_neighbours = vector<int>(4, -1);
	}

	void Tile::prepare_edges()
	{
		_edges.push_back(_image.top_edge());
		_edges.push_back(_image.right_edge());
		_edges.push_back(_image.bottom_edge());
		_edges.push_back(_image.left_edge());
		_edges.push_back(_image.top_reversed_edge());
		_edges.push_back(_image.right_reversed_edge());
		_edges.push_back(_image.bottom_reversed_edge());
		_edges.push_back(_image.left_reversed_edge());
	}

	void Tile::match_neighbours(int idx, const t_tiles& tiles)
	{
		// check if idx-th tile is my neighbour
		for (size_t i = 0; i < 4; i++)
		{
			int result = match(_edges[i], idx, tiles);
			if (result != -1)
				_neighbours[i] = idx;
		}
	}

	bool Tile::is_corner() const
	{
		return (_neighbours[left] == -1 || _neighbours[right] == -1)
			&& (_neighbours[top] == -1 || _neighbours[bottom] == -1);
	}

	bool Tile::is_top_left_corner() const
	{
		return (_neighbours[top] == -1 && _neighbours[left] == -1);
	}

	void Tile::match_vertically(Tile* ref)
	{
		// match ref(right_edge) with this(left_edge)
		int ref_right_edge = ref->_image.right_edge();
		int matching_edge = 0;
		while (_edges[matching_edge] != ref_right_edge) matching_edge++;

		switch (matching_edge)
		{
		case 0: // top
			_image.rotate_counterclockwise();
			_image.flip_horizontally();
			rotate_neighbours_counterclockwise();
			flip_neighbours_horizontally();
			break;

		case 1: // right
			_image.flip_vertically();
			flip_neighbours_vertically();
			break;

		case 2: // bottom
			_image.rotate_counterclockwise();
			_image.flip_vertically();
			rotate_neighbours_counterclockwise();
			flip_neighbours_vertically();
			break;

		case 3: // left
			_image.flip_horizontally();
			flip_neighbours_horizontally();
			break;

		case 4: // top reversed
			_image.rotate_counterclockwise();
			rotate_neighbours_counterclockwise();
			break;

		case 5: // right reversed
			_image.flip_horizontally();
			_image.flip_vertically();
			flip_neighbours_horizontally();
			flip_neighbours_vertically();
			break;

		case 6: // bottom reversed
			_image.rotate_clockwise();
			rotate_neighbours_clockwise();
			break;

		case 7: // left reversed
			// no correction
			break;
		}

		_edges.clear();
		prepare_edges();
	}

	void Tile::match_horizontally(Tile* ref)
	{
		// match ref(bottom_edge) with this(top_edge)
		int ref_right_edge = ref->_image.bottom_edge();
		int matching_edge = 0;
		while (_edges[matching_edge] != ref_right_edge) matching_edge++;

		switch (matching_edge)
		{
		case 0: // top
			_image.flip_vertically();
			flip_neighbours_vertically();
			break;

		case 1: // right
			_image.rotate_counterclockwise();
			_image.flip_vertically();
			rotate_neighbours_counterclockwise();
			flip_neighbours_vertically();
			break;

		case 2: // bottom
			_image.flip_horizontally();
			flip_neighbours_horizontally();
			break;

		case 3: // left
			_image.rotate_clockwise();
			_image.flip_vertically();
			rotate_neighbours_clockwise();
			flip_neighbours_vertically();
			break;

		case 4: // top reversed
			// no correction
			break;

		case 5: // right reversed
			_image.rotate_counterclockwise();
			rotate_neighbours_counterclockwise();
			break;

		case 6: // bottom reversed
			_image.flip_horizontally();
			_image.flip_vertically();
			flip_neighbours_horizontally();
			flip_neighbours_vertically();
			break;

		case 7: // left reversed
			_image.rotate_clockwise();
			rotate_neighbours_clockwise();
			break;
		}

		_edges.clear();
		prepare_edges();
	}

	void Tile::flip_neighbours_horizontally()
	{
		swap(_neighbours[top], _neighbours[bottom]);
	}

	void Tile::flip_neighbours_vertically()
	{
		swap(_neighbours[right], _neighbours[left]);
	}

	void Tile::rotate_neighbours_clockwise()
	{
		auto tmp = _neighbours[left];
		_neighbours[left] = _neighbours[bottom];
		_neighbours[bottom] = _neighbours[right];
		_neighbours[right] = _neighbours[top];
		_neighbours[top] = tmp;
	}

	void Tile::rotate_neighbours_counterclockwise()
	{
		auto tmp = _neighbours[top];
		_neighbours[top] = _neighbours[right];
		_neighbours[right] = _neighbours[bottom];
		_neighbours[bottom] = _neighbours[left];
		_neighbours[left] = tmp;
	}

	int Tile::match(int edge, int idx, const t_tiles& tiles)
	{
		// check if edge matches any edges of idx-th tile (-1 = no match)
		for (int i = 0; i < 8; i++)
			if (tiles[idx]->_edges[i] == edge)
				return i;

		return -1;
	}

	pair<t_tiles, size_t> Main::load(const vector<string>& input)
	{
		// load from input
		t_tiles tiles;
		size_t idx = 0;
		for (; idx < input.size(); idx++)
		{
			const auto& header = input[idx];
			if (header == "")
				break;

			idx++;
			vector<string> image;
			for (; idx < input.size(); idx++)
			{
				const auto& line = input[idx];
				if (line == "")
					break;

				image.push_back(line);
			}

			tiles.push_back(new Tile(header, image));
		}
		
		// prepare edges
		for (auto& t : tiles)
			t->prepare_edges();

		// match neighbours
		for (size_t i = 0; i < tiles.size(); i++)
			for (size_t j = 0; j < tiles.size(); j++)
				if (i != j)
					tiles[i]->match_neighbours((int)j, tiles);

		// find top left corner
		size_t top_left = 0;
		for (size_t i = 0; i < tiles.size(); i++)
			if (tiles[i]->is_top_left_corner())
				top_left = i;

		// return data
		return make_pair(tiles, top_left);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		const auto [tiles, top_left] = load(input);

		int64_t result = 1;
		for (const auto& t : tiles)
			if (t->is_corner())
				result *= t->id();

		return result;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		const auto [tiles, top_left] = load(input);

		// tiles ordered
		t_tiles ordered(tiles.size());
		ordered[0] = tiles[top_left];
		size_t idx = ordered[0]->right_neighbour();

		// flip and rotate tiles and place them in correct order
		size_t n = (size_t)sqrt(tiles.size());
		for (size_t i = 1; i < tiles.size(); i++)
		{
			ordered[i] = tiles[idx];

			if (i < n)
				ordered[i]->match_vertically(ordered[i - 1]);
			else
				ordered[i]->match_horizontally(ordered[i - n]);

			if ((i % n) == n - 1)
				idx = ordered[i - (n - 1)]->bottom_neighbour();
			else
				idx = ordered[i]->right_neighbour();
		}

		// extract big picture
		size_t sn = tiles[0]->bitmap().size() - 2;
		t_bitmap big_bitmap(sn * n);
		for (size_t i = 0; i < ordered.size(); i++)
			for (size_t j = 0; j < sn; j++)
				big_bitmap[(i / n) * sn + j] += ordered[i]->bitmap()[j + 1].substr(1, sn);

		// look for monsters on eight variants of big picture
		Image big(big_bitmap);
		int hashes = INT_MAX;
		for (int i = 0; i < 8; i++)
		{
			if (i == 4)
				big.flip_horizontally();

			Image sea_of_monsters = big;
			sea_of_monsters.release_monsters();
			hashes = min(hashes, sea_of_monsters.count_hashes());

			big.rotate_clockwise();
		}

		return hashes;
	}
}
