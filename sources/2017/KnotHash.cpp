#include "KnotHash.h"

KnotHash::t_data KnotHash::_add = { 17, 31, 73, 47, 23 };

KnotHash::KnotHash()
:	_pos(0), _skip(0)
{
}

int KnotHash::mult(const string& input)
{
	string s;
	stringstream ss(input);
	
	while (getline(ss, s, ','))
		_lengths.push_back(stoi(s));

	init();
	single_round();
	return _data[0] * _data[1];
}

string KnotHash::hash(const string& input)
{
	_lengths = t_data(input.size());
	for (int i = 0; i < (int)input.size(); i++)
		_lengths[i] = input[i];

	_lengths.insert(_lengths.end(), _add.begin(), _add.end());

	init();
	for (int i = 0; i < 0x40; i++)
		single_round();

	string hash(0x20, '?');
	for (int i = 0; i < 0x10; i++)
	{
		int v = 0;
		for (int j = 0; j < 0x10; j++)
			v ^= _data[i * 0x10 + j];

		hash[i * 2] = hex(v >> 4);
		hash[i * 2 + 1] = hex(v & 0x0f);
	}

	return hash;
}

void KnotHash::init()
{
	_pos = 0;
	_skip = 0;
	_data = t_data(0x100);
	for (int i = 0; i < 0x100; i++)
		_data[i] = i;
}

char KnotHash::hex(int v) const
{
	return (v > 9) ? char(v + 'a' - 10) : char(v + '0');
}

void KnotHash::single_round()
{
	int ds = (int)_data.size();
	for (auto len : _lengths)
	{
		int min_i = ds + _pos;
		int max_i = min_i + len - 1;
		while (min_i < max_i)
		{
			swap(_data[min_i % ds], _data[max_i % ds]);
			min_i++;
			max_i--;
		}

		_pos += len + _skip;
		_pos %= ds;
		_skip++;
		_skip %= ds;
	}
}
