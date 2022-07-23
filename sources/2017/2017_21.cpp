#include "2017_21.h"

namespace Day21_2017
{
	Square::Square(size_t size /* = 0 */)
	{
		_pixels = vector<string>(size, string(size, ' '));
	}

	Square::Square(string input)
	{
		size_t pos = 0;
		while (pos != string::npos)
		{
			pos = input.find_first_of('/');
			if (pos != string::npos)
			{
				_pixels.push_back(input.substr(0, pos));
				input = input.substr(pos + 1);
			}
			else
				_pixels.push_back(input);
		}
	}

	bool Square::operator < (const Square& rhs) const
	{
		return _pixels < rhs._pixels;
	}

	void Square::rotate()
	{
		auto src = _pixels;
		for (size_t y = 0; y < src.size(); y++)
			for (size_t x = 0; x < src.size(); x++)
				_pixels[x][_pixels.size() - y - 1] = src[y][x];
	}

	void Square::flip()
	{
		auto src = _pixels;
		for (size_t y = 0; y < src.size(); y++)
			for (size_t x = 0; x < src.size(); x++)
				_pixels[y][_pixels.size() - x - 1] = src[y][x];
	}

	void Square::iterate(const t_rules& rules)
	{
		auto v = divide();
		for (size_t i = 0; i < v.size(); i++)
			v[i] = rules.find(v[i])->second;

		join(v);
	}

	size_t Square::count_pixels() const
	{
		size_t n = 0;
		for (const auto& s : _pixels)
			n += count_if(s.begin(), s.end(), [](char c) { return c == '#'; });

		return n;
	}

	vector<Square> Square::divide() const
	{
		size_t block_size = ((_pixels.size() & 1) == 0) ? 2 : 3;
		size_t count = _pixels.size() / block_size;

		vector<Square> v;
		for (size_t y = 0; y < count; y++)
			for (size_t x = 0; x < count; x++)
				v.push_back(piece(y * block_size, x * block_size, block_size));

		return v;
	}

	Square Square::piece(size_t sy, size_t sx, size_t size) const
	{
		Square s(size);
		for (size_t y = 0; y < size; y++)
			for (size_t x = 0; x < size; x++)
				s._pixels[y][x] = _pixels[y + sy][x + sx];

		return s;
	}

	void Square::join(const vector<Square>& v)
	{
		size_t block_size = v[0]._pixels.size();
		size_t joined_size = (int)sqrt(v.size()) * block_size;
		size_t count = joined_size / v[0]._pixels.size();

		Square dst(joined_size);
		int i = 0;
		for (size_t y = 0; y < count; y++)
			for (size_t x = 0; x < count; x++)
				dst.put(v[i++], y * block_size, x * block_size);

		_pixels = move(dst._pixels);
	}

	void Square::put(const Square& s, size_t sy, size_t sx)
	{
		size_t size = s._pixels.size();
		for (size_t y = 0; y < size; y++)
			for (size_t x = 0; x < size; x++)
				_pixels[y + sy][x + sx] = s._pixels[y][x];
	}

	t_rules Main::load(const vector<string>& input)
	{
		t_rules rules;
		for (const string& s : input)
		{
			size_t pos = s.find(" => ");
			Square in(s.substr(0, pos));
			Square out(s.substr(pos + 4));

			for (int i = 0; i < 8; i++)
			{
				t_rules::const_iterator it = rules.find(in);
				if (it == rules.end())
					rules[in] = out;

				in.rotate();
				if (i == 3)
					in.flip();
			}
		}

		return rules;
	}

	size_t Main::solve(const t_rules& rules, int iterations)
	{
		Square grid(".#./..#/###");
		for (int i = 0; i < iterations; i++)
			grid.iterate(rules);

		return grid.count_pixels();
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Main::solve(load(input), 5);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Main::solve(load(input), 18);
	}
}
