#ifndef __2023_15__
#define __2023_15__

#include "../shared/Solution.h"

namespace Day15_2023
{
	using LensSlot = vector<string>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static uint8_t hash(const string& input);
		static pair<string, int> split(const string& input);
		static void update(LensSlot& box, const string& label, const string& value);
		static void erase(LensSlot& box, const string& label);
		static size_t sum(const vector<LensSlot>& boxes);
	};
}

#endif
