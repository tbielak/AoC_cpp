#include "2019_08.h"

namespace Day08_2019
{
	t_layers load(const string& input)
	{
		const int width = 25;
		const int height = 6;
		int single_layer = width * height;
		size_t layer_count = input.size() / single_layer;

		t_layers layers(layer_count);
		for (size_t i = 0; i < layer_count; i++)
		{
			t_image image = t_image(height);
			for (size_t j = 0; j < height; j++)
				image[j] = input.substr(i * single_layer + j * width, width);

			layers[i] = move(image);
		}

		return layers;
	}

	size_t part_one(const t_layers& layers)
	{
		size_t min_zeroes_layer = 0;
		size_t min_zeroes = INT_MAX;
		for (size_t i = 0; i < layers.size(); i++)
		{
			size_t zeroes = 0;
			for (const auto& line : layers[i])
				zeroes += count(line.begin(), line.end(), '0');

			if (min_zeroes > zeroes)
			{
				min_zeroes = zeroes;
				min_zeroes_layer = i;
			}
		}

		size_t ones = 0;
		size_t twos = 0;
		for (const auto& line : layers[min_zeroes_layer])
		{
			ones += count(line.begin(), line.end(), '1');
			twos += count(line.begin(), line.end(), '2');
		}

		return ones * twos;
	}

	t_image part_two(const t_layers& layers)
	{
		const int width = 25;
		const int height = 6;
		string s(width, '?');
		t_image result(height, s);

		for (size_t y = 0; y < height; y++)
			for (size_t x = 0; x < width; x++)
				for (const auto& image : layers)
				{
					if (image[y][x] == '0')
					{
						result[y][x] = ' ';
						break;
					}

					if (image[y][x] == '1')
					{
						result[y][x] = -37;
						break;
					}
				}

		return result;
	}

	t_output main(const t_input& input)
	{
		t_layers layers = load(input[0]);

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(layers);
		auto p2 = part_two(layers);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.insert(solutions.end(), p2.begin(), p2.end());
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
