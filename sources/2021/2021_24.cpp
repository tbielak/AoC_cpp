#include "2021_24.h"

// explained here:
// https://github.com/tbielak/AoC_cpp/blob/master/doc/2021_24.md

namespace Day24_2021
{
	Solver::Solver(const vector<string>& input, int w_init)
	:	_w_init(w_init), _step(w_init == 9 ? -1 : 1)
	{
		for (int i = 0; i < 14; i++)
		{
			_A.push_back(stoi(input[i * 18 + 4].substr(6)));
			_B.push_back(stoi(input[i * 18 + 5].substr(6)));
			_C.push_back(stoi(input[i * 18 + 15].substr(6)));
		}

		_w = vector<int>(14, w_init);

		int64_t z = 1;
		for (int i = 0; i < 14; i++)
		{
			if (_A[i] == 1)
				z *= 26;
			else
				z /= 26;

			_max_z.push_back(z);
		}
	}

	int64_t Solver::execute_block(int64_t z, size_t i)
	{
		int64_t x = z % 26;
		z /= _A[i];

		if (x + _B[i] == _w[i])
			return z;

		return z * 26 + _w[i] + _C[i];
	}

	string Solver::execute()
	{
		int64_t z = -1;
		while (z != 0)
		{
			z = 0;
			for (size_t i = 0; i < _w.size(); i++)
			{
				z = execute_block(z, i);
				if (z > _max_z[i])
				{
					_w[i] += _step;
					while ((_w[i] % 10) == 0)
					{
						_w[i--] = _w_init;
						_w[i] += _step;
					}

					for (size_t j = i + 1; j < _w.size(); j++)
						_w[j] = _w_init;

					break;
				}
			}
		}

		string result;
		for (auto v : _w)
			result += to_string(v);

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver(input, 9).execute();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Solver(input, 1).execute();
	}
}
