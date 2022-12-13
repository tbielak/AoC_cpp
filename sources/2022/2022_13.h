#ifndef __2022_13__
#define __2022_13__

#include "../shared/Solution.h"

namespace Day13_2022
{
	class Element
	{
	public:
		Element(const string& input);
		const string& input() const;

		int compare(Element& right);	// left = this

	private:
		Element();
		Element(int value);
		size_t load(string input, size_t pos);
		void convert_to_list();

		int _value;
		bool _is_value;
		vector<Element> _list;
		string _input;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int find(const vector<Element>& vec, const string& input);
	};
}

#endif
