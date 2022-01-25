#include "2019_18.h"

namespace Day18_2019
{
	Position::Position(int row /* = 0 */, int col /* = 0 */)
	:	row(row), col(col)
	{
	}

	bool Position::operator < (const Position& other) const
	{
		return (row == other.row) ? col < other.col : row < other.row;
	}

	KeyRing::KeyRing(int count /* = 0 */)
	:	_bitset(0), _all((1 << count) - 1)
	{
	}

	bool KeyRing::operator < (const KeyRing& other) const
	{
		return _bitset < other._bitset;
	}

	void KeyRing::add(int i)
	{
		_bitset |= (1 << i);
	}

	void KeyRing::drop(int i)
	{
		_bitset &= ~(1 << i);
	}

	bool KeyRing::available(int i) const
	{
		return (_bitset & (1 << i));
	}

	bool KeyRing::all() const
	{
		return _bitset == _all;
	}

	bool Cache::update(const KeyRing& keys, const t_positions& positions, int steps)
	{
		auto k = make_pair(keys, positions);
		auto it = _map.find(k);
		if (it != _map.end() && it->second <= steps)
			return true;

		_map[k] = steps;
		return false;
	}

	Solver::Solver(const t_labyrinth& lab)
	:   _shortest(INT_MAX), _lab(lab)
	{
		int key_count = 0;
		for (int row = 0; row < (int)_lab.size(); row++)
			for (int col = 0; col < (int)_lab[0].size(); col++)
			{
				// find starting position
				if (_lab[row][col] == '@')
				{
					_start = { Position(row, col) };
					_lab[row][col] = '.';
				}

				// find number of keys in labyrinth
				if (_lab[row][col] >= 'a' && _lab[row][col] <= 'z')
				{
					int k = _lab[row][col] - 'a' + 1;
					key_count = max(k, key_count);
				}
			}

		_keys = KeyRing(key_count);
	}

	void Solver::four_robots()
	{
		// fix labyrinth
		int starting_row = _start[0].row;
		int starting_col = _start[0].col;
		for (int row = -1; row <= 1; row++)
			for (int col = -1; col <= 1; col++)
				_lab[starting_row + row][starting_col + col] = _lab_update[row + 1][col + 1];

		// four starting points
		_start = {
			Position(starting_row - 1, starting_col - 1),
			Position(starting_row - 1, starting_col + 1),
			Position(starting_row + 1, starting_col - 1),
			Position(starting_row + 1, starting_col + 1)
		};
	}

	int Solver::execute()
	{
		recursive_search(_start, 0);
		return _shortest;
	}

	void Solver::recursive_search(t_positions& positions, int steps)
	{
		if (_keys.all())
		{
			// all keys found!
			_shortest = min(_shortest, steps);
			return;
		}

		if (steps >= _shortest)
			// don't go further because already too many steps
			return;

		if (_cache.update(_keys, positions, steps))
			// don't go further because path is already cached
			return;

		for (auto& pos : positions)
		{
			// distance matrix, all distances = infinity
			t_distance distance(_lab.size(), vector<int>(_lab[0].size(), INT_MAX));

			// 0 steps from me to me
			distance[pos.row][pos.col] = 0;

			// queue of positions to check
			queue<Position> q;
			q.push(pos);

			while (q.size() > 0)
			{
				// get position to check
				Position current = q.front();
				q.pop();

				// try to go in four available directions
				for (Position move : _directions)
				{
					// making move
					Position new_position = Position(current.row + move.row, current.col + move.col);

					// note: labyrinth has outside walls => no need to check boundaries
					// hitting the wall?
					char tile = _lab[new_position.row][new_position.col];
					if (tile == '#')
						continue;

					// distance after making a move
					int new_distance = distance[current.row][current.col] + 1;

					// check what is  place
					bool ok = false;
					if (tile == '.' || _keys.available(tile - 'a'))
						// free space or already available key
						ok = true;
					else
						if (tile >= 'A' && tile <= 'Z' && _keys.available(tile - 'A'))
							// the door to which we have the key
							ok = true;
						else
							// we found a new key
							if (tile >= 'a' && tile <= 'z')
							{
								// add it to the key ring
								_keys.add(tile - 'a');
								
								// remember current position, update position and explore new situation recursively
								Position tmp = pos;
								pos = new_position;
								recursive_search(positions, steps + new_distance);

								// back to previous position and drop the key
								pos = tmp;
								_keys.drop(tile - 'a');
							}

					// we can go there and found shorter distance
					if (ok && distance[new_position.row][new_position.col] > new_distance)
					{
						// remember shorter distance
						distance[new_position.row][new_position.col] = new_distance;

						// explore using shorter distance
						q.push(new_position);
					}
				}
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver(input).execute();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		Solver s(input);
		s.four_robots();
		return s.execute();
	}
}
