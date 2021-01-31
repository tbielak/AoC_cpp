#ifndef __2015_13__
#define __2015_13__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
