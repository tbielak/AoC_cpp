#ifndef __2020_07__
#define __2020_07__

#include "../shared/input_output.h"

namespace Day07_2020
{
	typedef map<string, size_t> t_bagsmap;
	typedef pair<string, size_t> t_bag;
	typedef vector<vector<t_bag>> t_inside;

	class Luggage
	{
	public:
		Luggage(const vector<string>& input);

		size_t at_least_one(const string& key) const;
		size_t count_bags(const string& color) const;

	private:
		t_bagsmap _bags;
		t_inside _inside;

		bool contains_shiny_gold(const string& color, const string& key) const;
	};

	t_output main(const t_input& input);
}

#endif
