#include "2019_16.h"

namespace Day16_2019
{
	int iabs(int x)
	{
		return (x < 0) ? -x : x;
	}

	string part_one(const string& input)
	{
		size_t size = input.size();
		t_vecInt2 pattern = t_vecInt2(size, t_vecInt());

		vector<int> wave = { 0, 1, 0, -1 };
		for (size_t i = 0; i < size; i++)
		{
			size_t vp = (i == 0) ? 1 : 0;
			size_t rep_max = i + 1;
			size_t rep_count = (i == 0) ? 0 : 1;

			pattern[i] = t_vecInt(size);
			for (size_t j = 0; j < size; j++)
			{
				pattern[i][j] = wave[vp];
				rep_count++;
				if (rep_count == rep_max)
				{
					vp++;
					vp &= 3;
					rep_count = 0;
				}
			}
		}

		t_vecInt v = t_vecInt(size);
		t_vecInt r = t_vecInt(size);
		for (size_t i = 0; i < size; i++)
			v[i] = input[i] - '0';

		for (size_t phases = 0; phases < 100; phases++)
		{
			for (size_t i = 0; i < size; i++)
			{
				r[i] = 0;
				for (size_t j = 0; j < size; j++)
					r[i] += v[j] * pattern[i][j];
			}

			for (size_t i = 0; i < size; i++)
				v[i] = iabs(r[i] % 10);
		}

		string result;
		for (size_t i = 0; i < 8; i++)
			result += char(v[i] + '0');

		return result;
	}

	string part_two(const string& input)
	{
		size_t size = input.size();
		size_t repeat = 10000;
		size_t total = size * repeat;

		size_t offset = stoi(input.substr(0, 7));
		size_t length = total - offset;

		t_vecInt v = t_vecInt(length);
		size_t j = offset % size;
		for (size_t i = 0; i < length; i++)
		{
			v[i] = input[j++] - '0';
			j %= size;
		}

		for (size_t phase = 0; phase < 100; phase++)
		{
			size_t x = length - 2;
			while (1)
			{
				v[x] = (v[x] + v[x + 1]) % 10;
				if (x == 0)
					break;

				x--;
			}
		}

		string result;
		for (size_t i = 0; i < 8; i++)
			result += char(v[i] + '0');

		return result;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input[0]);
		auto p2 = part_two(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(p1);
		solutions.push_back(p2);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
