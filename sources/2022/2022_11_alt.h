#ifndef __2022_11_alt__
#define __2022_11_alt_

#include "../shared/Solution.h"

namespace Day11_2022_Alt
{
	class Monkey
	{
	public:
		typedef int64_t(*compute_function)(int64_t, int64_t);
		static int64_t compute_power(int64_t a, int64_t b) { (void)(b); return a * a; }
		static int64_t compute_mult(int64_t a, int64_t b) { return a * b; }
		static int64_t compute_add(int64_t a, int64_t b) { return a + b; }

		Monkey(const string& items_str, const string& operation_str,
			const string& divisible_str, const string& true_target_str, const string& false_target_str);

		vector<int64_t> items;
		int value;
		int divisible;
		vector<int> target;
		compute_function compute;

	private:
		void load_items(const string& items_str);
		void load_operation(const string& operation_str);
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
