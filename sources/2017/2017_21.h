#ifndef __2017_21__
#define __2017_21__

#include "../shared/Solution.h"

namespace Day21_2017
{
	class Square;
	typedef map<Square, Square> t_rules;

	class Square
	{
	public:
		Square(size_t size = 0);
		Square(string input);
		
		bool operator < (const Square& rhs) const;
		
		void rotate();
		void flip();
		void iterate(const t_rules& rules);
		size_t count_pixels() const;

	private:
		vector<string> _pixels;

		vector<Square> divide() const;
		Square piece(size_t sy, size_t sx, size_t size) const;
		
		void join(const vector<Square>& v);
		void put(const Square& s, size_t sy, size_t sx);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_rules load(const vector<string>& input);
		static size_t solve(const t_rules& rules, int iterations);
	};
}

#endif
