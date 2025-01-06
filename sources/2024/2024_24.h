#ifndef __2024_24__
#define __2024_24__

#include "../shared/Solution.h"

namespace Day24_2024
{
	constexpr auto UNDEFINED = -1;
	constexpr auto INPUT1 = 0;
	constexpr auto TYPE = 1;
	constexpr auto INPUT2 = 2;
	constexpr auto OUTPUT = 3;

	class Device
	{
	public:
		Device(const vector<string>& input);
		Device& simulate();
		int64_t z_wires_output();
		string eight_wires();

	private:
		map<string, int> _wires;
		vector<vector<string>> _gates;
		set<string> _swapped;

		void add_wire(const string& name, int value = UNDEFINED);
		string find_output(const string& a, const string& type, const string& b) const;
		void swap_outputs(const string& a, const string& b);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
