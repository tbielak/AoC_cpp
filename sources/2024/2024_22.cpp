#include "2024_22.h"

namespace Day22_2024
{
	vector<int64_t> Main::load(const vector<string>& input)
	{
		vector<int64_t> numbers;
		for (const string& s : input)
			numbers.push_back(stoi(s));

		return numbers;
	}

	int64_t Main::next(int64_t v)
	{
		v = ((v * 64) ^ v) % 16777216;
		v = ((v / 32) ^ v) % 16777216;
		v = ((v * 2048) ^ v) % 16777216;
		return v;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto numbers = load(input);

		int64_t sum = 0;
		for (auto n : numbers)
		{
			for (int i = 0; i < 2000; i++)
				n = next(n);

			sum += n;
		}

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		typedef map<int, int> t_seqprice;	// map four diff sequence to price
		t_seqprice bannanas;

		auto numbers = load(input);
		for (auto n : numbers)
		{
			int seq = 0;
			t_seqprice buyer;
			for (int i = 0; i < 2000; i++)
			{
				int64_t nn = next(n);
				int diff = int((nn % 10) - (n % 10));
				int price = int(nn % 10);
				n = nn;

				seq = (seq * 100 + (diff + 10)) % 100000000;
				if (i > 3 && buyer.find(seq) == buyer.end())
					buyer[seq] += price;
			}

			for (const auto& [seq, price] : buyer)
				bannanas[seq] += price;
		}

		int result = 0;
		for (const auto& [_, price] : bannanas)
			result = max(result, price);

		return result;
	}
}
