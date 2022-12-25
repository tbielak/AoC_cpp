#ifndef __2022_17__
#define __2022_17__

#include "../shared/Solution.h"

namespace Day17_2022
{
	class Tetris
	{
	public:
		Tetris(const string& jet_pattern);

		int64_t run(int64_t count);

	private:
		size_t _rock_idx;
		size_t _jet_idx;
		string _jet_pattern;
		vector<string> _chamber;
		static vector<vector<string>> _rocks;
		size_t _height;
		size_t _skipped;

		void put_next_rock();
		int rock_line() const;
		int pushing_direction();
		void try_to_push(int start, int direction);
		int fall_possible(int i) const;
		void fall(int i);
		void remove_empty_rows();
		void settle_down(int start);
		void shorten_chamber(int maxlines);
		void drop_rock();
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
