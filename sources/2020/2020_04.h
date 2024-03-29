#ifndef __2020_04__
#define __2020_04__

#include "../shared/Solution.h"

namespace Day04_2020
{
	typedef map<string, string> t_fields;
	typedef vector<t_fields> t_passports;

	class CheckEngine
	{
	public:
		CheckEngine(const vector<string>& input);

		size_t complete_count() const;
		size_t valid_count() const;

	private:
		t_passports _passports;

		void load_passport(const string& input);
		bool is_number(const string& s) const;
		bool yr_check(const string& s, int yr_min, int yr_max) const;
		bool hgt_check(const string& s) const;
		bool hcl_check(const string& s) const;
		bool ecl_check(const string& s) const;
		bool pid_check(const string& s) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
