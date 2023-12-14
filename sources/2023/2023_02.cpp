#include "2023_02.h"

namespace Day02_2023
{
	Cube::Cube(const string& s)
	{
		r = find(s, "red");
		g = find(s, "green");
		b = find(s, "blue");
	}

	int Cube::find(const string& s, const string& name)
	{
		size_t pos = s.find(" " + name);
		if (pos == string::npos)
			return 0;

		do
		{
			pos--;
		} while (pos > 0 && isdigit(s[pos]));

		return stoi(s.substr(pos));
	}

	vector<Cube> Main::load(string s)
	{
		vector<Cube> cubes;
		while (1)
		{
			size_t pos = s.find(";");
			if (pos == string::npos)
			{
				cubes.push_back(Cube(s));
				return cubes;
			}
			else
			{
				cubes.push_back(Cube(s.substr(0, pos)));
				s = s.substr(pos + 1);
			}
		}
	}

	Games Main::load(const vector<string>& input)
	{
		Games games;
		for (const string& s : input)
		{
			size_t pos = s.find_first_of(":");
			int id = stoi(s.substr(5, pos - 5));
			games[id] = load(s.substr(pos + 1));
		}

		return games;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int sum = 0;
		for (const auto [id, gm] : load(input))
		{
			bool ok = true;
			for (const auto& c : gm)
				if (c.r > 12 || c.g > 13 || c.b > 14)
					ok = false;

			if (ok)
				sum += id;
		}

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int sum = 0;
		for (const auto [id, gm] : load(input))
		{
			int r = 0;
			int g = 0;
			int b = 0;
			for (const auto& c : gm)
			{
				r = max(r, c.r);
				g = max(g, c.g);
				b = max(b, c.b);
			}

			sum += r * g * b;
		}

		return sum;
	}
}
