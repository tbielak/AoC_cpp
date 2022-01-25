#ifndef __2015_13__
#define __2015_13__

#include "../shared/Solution.h"

namespace Day13_2015
{
	class Input
	{
	public:
		Input(const string& person1, const string& person2, int happiness);

		string person1;
		string person2;
		int happiness;
	};

	typedef vector<Input> t_vecInput;

	class Happiness
	{
	public:
		Happiness();
		
		void create_persons(const t_vecInput& input);
		void add_me();
		
		void who_likes_who(const t_vecInput& input);
		int max_happiness();

	private:
		typedef map<string, int> t_persons;
		t_persons _persons;
		vector<vector<int>> _likes;
		vector<int> _setup;

		void add_person(const string& s);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int solve(const vector<string>& input, bool with_me);
	};
}

#endif
