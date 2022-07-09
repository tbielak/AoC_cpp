#include "2018_10.h"

namespace Day10_2018
{
	void Points::step()
	{
		for (size_t i = 0; i < x.size(); i++)
		{
			x[i] += vx[i];
			y[i] += vy[i];
		}
	}

	int Points::height() const
	{
		return *max_element(y.begin(), y.end()) - *min_element(y.begin(), y.end());
	}

	vector<string> Points::image() const
	{
		int ymin = *min_element(y.begin(), y.end());
		int ymax = *max_element(y.begin(), y.end());
		int xmin = *min_element(x.begin(), x.end());
		int xmax = *max_element(x.begin(), x.end());

		vector<string> v = vector<string>(ymax - ymin + 1, string(xmax - xmin + 1, ' '));
		for (size_t i = 0; i < x.size(); i++)
			v[y[i] - ymin][x[i] - xmin] = -37;

		return v;
	}

	Points Main::load(const vector<string>& input)
	{
		Points pts;
		for (auto s : input)
		{
			size_t comma = s.find_first_of(',');
			pts.x.push_back(stoi(s.substr(10, comma - 10)));
			size_t end = s.find_first_of('>');
			pts.y.push_back(stoi(s.substr(comma + 1, end - comma)));
			s = s.substr(end + 2);

			comma = s.find_first_of(',');
			pts.vx.push_back(stoi(s.substr(10, comma - 10)));
			end = s.find_first_of('>');
			pts.vy.push_back(stoi(s.substr(comma + 1, end - comma)));
		}

		return pts;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		auto pts = load(input);
		int seconds = 0;
		while (1)
		{
			pts.step();
			seconds++;
			if (pts.height() <= 10)
				break;
		}

		vector<string> result = pts.image();
		result.push_back(to_string(seconds));
		return result;
	}
}
