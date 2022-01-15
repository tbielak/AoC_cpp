#include "2016_14.h"

// use code shared between 2015 and 2016 solutions
#define MD5_SINGLE_TRANSFORM_PREFIX
#define MD5_SINGLE_TRANSFORM_FNAME Day_14_2016_md5_single_transform
#define MD5_SINGLE_TRANSFORM_RETURNS_STRING
#include "../MD5/MD5_single_transform.h"

namespace Day14_2016
{
	string md5(const string& hash)
	{
		// copy input to 64-byte buffer, required for single MD5 transform
		vector<unsigned char> buffer(64, 0);
		copy(hash.begin(), hash.end(), buffer.begin());

		// place 0x80 at the end of the string to create correct MD5 padding
		buffer[hash.size()] = 0x80;

		// place 16-bit length (in bits) of the string at 56/57th buffer element, as required by MD5 padding
		(*(int16_t *)(&buffer[56])) = (int16_t)(hash.size() * 8);

		// do one MD5 transform and get MD5 hash as string
		return MD5_SINGLE_TRANSFORM_FNAME((unsigned int*)(&buffer[0]));
	}

	string find_hash(t_hash_cache& cache, string input, int i, int additional_hashings)
	{
		// input hash
		input += to_string(i);

		// already known?
		t_hash_cache::const_iterator it = cache.find(input);
		if (it != cache.end())
			return it->second;

		// do md5
		string hash = input;
		for (int i = 0; i <= additional_hashings; i++)
			hash = md5(hash);

		// store in cache and return
		cache[input] = hash;
		return hash;
	}

	// the same character three times in a row -> return it
	char triplet(const string& hash)
	{
		for (int i = 0; i < 30; i++)
			if (hash[i] == hash[i + 1] && hash[i + 1] == hash[i + 2])
				return hash[i];

		return 0;
	}

	// the same c character five times in a row?
	bool funflet(char c, const string& hash)
	{
		string k(5, c);
		return hash.find(k) != string::npos;
	}

	// solution
	int find_index(const string& input, int additional_hashings = 0)
	{
		int index = 0;
		int keys = 0;
		t_hash_cache cache;

		while (keys < 64)
		{
			string hash = find_hash(cache, input, index, additional_hashings);
			char t = triplet(hash);
			if (t != 0)
			{
				for (int i = index + 1; i <= index + 1000; i++)
				{
					hash = find_hash(cache, input, i, additional_hashings);
					if (funflet(t, hash))
					{
						keys++;
						break;
					}
				}
			}

			index++;
		}

		return index - 1;
	}

	int part_one(const string& input)
	{
		return find_index(input);
	}

	int part_two(const string& input)
	{
		return find_index(input, 2016);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input[0]);
		auto p2 = part_two(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
