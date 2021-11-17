#ifndef __2019_14__
#define __2019_14__

#include "../shared/input_output.h"

namespace Day14_2019
{
	class Ingredient
	{
	public:
		Ingredient();
		Ingredient(const string& input);

		string name;
		int count;
	};

	typedef vector<Ingredient> t_ingredients;

	class Chemical
	{
	public:
		Chemical(const string& ingredients_string, const string& target, int order = -1);

		int order;
		Ingredient target;
		t_ingredients ingredients;

	private:
		string ltrim(const string& s);
	};

	typedef vector<Chemical> t_chemicals;

	class Reactions
	{
	public:
		void add(const string& line);
		void prepare();

		intmax_t produce_fuel(intmax_t amount) const;
		intmax_t target_ore(intmax_t ore) const;

	private:
		t_chemicals _chemicals;
		map<string, size_t> _names;

		static bool sort_proc(const Chemical& x1, const Chemical& x2);
		void order_recursive(const string& name, int order);
		void update_names_mapping();
	};

	t_output main(const t_input& input);
}

#endif
