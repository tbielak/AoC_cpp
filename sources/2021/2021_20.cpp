#include "2021_20.h"

namespace Day20_2021
{
	int Main::is_hash(char c)
	{
		return (c == '#') ? 1 : 0;
	}

	int Main::get_idx(const t_image& image, int x, int y, int width, int height, char empty)
	{
		int idx = 0;
		int bit = 256;
		for (int dy = -1; dy <= 1; dy++)
			for (int dx = -1; dx <= 1; dx++)
			{
				int ny = y + dy;
				int nx = x + dx;
				if (ny >= 0 && ny < height && nx >= 0 && nx < width)
					idx += is_hash(image[ny][nx]) * bit;
				else
					idx += is_hash(empty) * bit;

				bit >>= 1;
			}

		return idx;
	}

	t_image Main::enhance(const string& algorithm, const t_image& src, char& empty)
	{
		// source and destination image sizes
		int src_height = (int)src.size();
		int src_width = (int)src[0].size();
		int dst_height = src_height + 2;
		int dst_width = src_width + 2;
		
		// make larger image
		t_image dst = t_image(dst_height, string(dst_width, '.'));

		// put pixels
		for (int y = 0; y < dst_height; y++)
			for (int x = 0; x < dst_width; x++)
				dst[y][x] = algorithm[get_idx(src, x - 1, y - 1, src_width, src_height, empty)];

		// prepare default value (new places) for next step
		empty = (empty == '#') ? algorithm[511] : algorithm[0];
		return dst;
	}

	int Main::solve(int steps, const vector<string>& input)
	{
		// load
		string algorithm = input[0];
		t_image image;
		for (int i = 2; i < (int)input.size(); i++)
			image.push_back(input[i]);

		// enhance
		char empty = '.';
		for (int i = 1; i <= steps; i++)
			image = enhance(algorithm, image, empty);

		// count
		int count = 0;
		for (const auto& s : image)
			count += (int)count_if(s.begin(), s.end(), [](auto c) { return c == '#'; });

		return count;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(2, input);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(50, input);
	}
}
