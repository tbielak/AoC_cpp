#ifndef __2020_24__
#define __2020_24__

#include "../shared/input_output.h"

namespace Day24_2020
{
	typedef pair<int, int> t_point;

	class Lobby
	{
	public:
		Lobby(const vector<string>& input);

		size_t count_blacks() const;
		void create_floor();
		void living_art();

		int adjacent(int y, int x) const;
		size_t count_blacks_on_the_floor() const;

	private:
		set<t_point> _blacks;
		vector<vector<bool>> _floor;
		int _xmin, _xmax, _ymin, _ymax;
		int _width, _height;
	};

	t_output main(const t_input& input);
}

#endif
