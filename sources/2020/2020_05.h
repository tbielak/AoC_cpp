#ifndef __2020_05__
#define __2020_05__

#include "../shared/input_output.h"

namespace Day05_2020
{
	typedef pair<int, int> t_seat;
	typedef vector<t_seat> t_vecseat;

	class Boarding
	{
	public:
		Boarding(const vector<string>& input);
		
		int max_sid() const;
		int my_seat_sid() const;

	private:
		t_vecseat _seats;
		int _maxr, _maxc;

		int binary_search(const string& s, char direction);
	};

	t_output main(const t_input& input);
}

#endif
