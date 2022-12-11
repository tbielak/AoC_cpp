#ifndef __2022_11__
#define __2022_11__

#include "../shared/Solution.h"

namespace Day11_2022
{
	class Monkey
	{
	public:
		Monkey(const string& items, const string& operation,
			const string& divisible, const string& true_target, const string& false_target);
		
		pair<size_t, int64_t> turn(size_t idx, int decrease_worry_level);
		void add_item(int64_t value);
		void clear_items();
		int divisible() const;
		size_t items_count() const;

	private:
		void load_items(const string& items);
		void load_operation(const string& operation);

		vector<int64_t> _items;
		function<int64_t(int64_t, int64_t)> _operation_fn;
		int _value;
		int _divisible;
		vector<int> _target;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Monkey> load(const vector<string>& input);
		static int64_t keep_away(vector<Monkey> monkeys, int rounds, int decrease_worry_level);
	};
}

#endif
