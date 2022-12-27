#include "2022_20.h"

namespace Day20_2022
{
	Data::Data(const vector<string>& input, int64_t decryption_key /* = 1 */)
	:	_zero_idx(-1)
	{
		for (int i = 0; i < (int)input.size(); i++)
			_data.push_back(make_pair(i, stoll(input[i]) * decryption_key));

		_size = (int)_data.size();
	}

	int64_t Data::decode(int rounds /* = 1 */)
	{
		for (int r = 0; r < rounds; r++)
			for (int i = 0; i < _size; i++)
			{
				int64_t idx = 0;
				while (_data[idx].first != i) idx++;

				auto tmp = _data[idx];
				_data.erase(_data.begin() + idx);
				_data.insert(_data.begin() + target(idx + tmp.second, _size - 1), tmp);
			}

		_zero_idx = 0;
		while (_data[_zero_idx].second != 0) _zero_idx++;

		return get(1000) + get(2000) + get(3000);
	}

	int64_t Data::target(int64_t a, int64_t b) const
	{
		return (a % b + b) % b;
	}

	int64_t Data::get(int idx) const
	{
		return _data[(_zero_idx + idx) % _size].second;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Data(input).decode();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Data(input, 811589153).decode(10);
	}
}
