#include "2017_10.h"

namespace Day10_2017
{
	void Main::Knot_Hash_single_round(t_data& data, const t_data& lengths, int& pos, int& skip_size)
	{
		int ds = (int)data.size();
		for (auto len : lengths)
		{
			int min_i = ds + pos;
			int max_i = min_i + len - 1;
			while (min_i < max_i)
			{
				swap(data[min_i % ds], data[max_i % ds]);
				min_i++;
				max_i--;
			}

			pos += len + skip_size;
			pos %= ds;
			skip_size++;
			skip_size %= ds;
		}
	}

	AoC::Output Main::part_one(const string& input)
	{
		t_data lengths;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			lengths.push_back(stoi(s));

		t_data data(0x100);
		for (int i = 0; i < 0x100; i++)
			data[i] = i;
		
		int pos = 0;
		int skip_size = 0;
		Knot_Hash_single_round(data, lengths, pos, skip_size);

		return data[0] * data[1];
	}

	char Main::hex(int v)
	{
		return (v > 9) ? char(v + 'a' - 10) : char(v + '0');
	}

	AoC::Output Main::part_two(const string& input)
	{
		t_data lengths(input.size());
		for (int i = 0; i < (int)input.size(); i++)
			lengths[i] = input[i];

		static t_data add = { 17, 31, 73, 47, 23 };
		lengths.insert(lengths.end(), add.begin(), add.end());

		t_data data(0x100);
		for (int i = 0; i < 0x100; i++)
			data[i] = i;

		int pos = 0;
		int skip_size = 0;
		for (int i = 0; i < 0x40; i++)
			Knot_Hash_single_round(data, lengths, pos, skip_size);
		
		string hash(0x20, '?');
		for (int i = 0; i < 0x10; i++)
		{
			int v = 0;
			for (int j = 0; j < 0x10; j++)
				v ^= data[i * 0x10 + j];

			hash[i * 2] = hex(v >> 4);
			hash[i * 2 + 1] = hex(v & 0x0f);
		}

		return hash;
	}
}
