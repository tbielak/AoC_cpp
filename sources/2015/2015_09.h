#ifndef __2015_09__
#define __2015_09__

#include "../shared/Solution.h"

namespace Day09_2015
{
	class Distance
	{
	public:
		Distance(const string& from, const string& to, int distance);

		string from;
		string to;
		int distance;
	};

	typedef vector<Distance> t_vecDistance;

	class World
	{
	public:
		World(const t_vecDistance& input);

		void travel_to(size_t i);
		void tournee();

		int shortest() const { return _shortest; }
		int longest() const { return _longest; }

	private:
		map<string, size_t> _places;
		vector<vector<int>> _distances;
		vector<bool> _visited;
		int _shortest;
		int _longest;
		int _length;

		void add_place(const string& p);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static t_vecDistance load(const vector<string>& input);
	};
}

#endif
