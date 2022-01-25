#ifndef __2020_21__
#define __2020_21__

#include "../shared/Solution.h"

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

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);	
	};
}

#endif
