#ifndef __2020_21__
#define __2020_21__

#include "../shared/input_output.h"

namespace Day21_2020
{
	class Food
	{
	public:
		Food(const vector<string>& input);

		void solve();

		size_t safe_count() const;
		string safe_chain() const;

	private:
		vector<string> _input;
		vector<string> _ingredients;
		map<string, set<string>> _allergens;

		set<string> add_ingredients(const string& input);
		void add_allergens(const string& input, const set<string>& ing);
	};

	t_output main(const t_input& input);
}

#endif
