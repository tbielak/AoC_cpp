#ifndef __2017_KnotHash__
#define __2017_KnotHash__

#include "../shared/stl.h"

// KnotHash class computes Kont Hash :)
// It is used in 10/2017 and 14/2027 solutions

class KnotHash
{
public:
	typedef vector<int> t_data;

	KnotHash();

	int mult(const string& input);
	string hash(const string& input);

private:
	int _pos;
	int _skip;
	t_data _lengths;
	t_data _data;

	static t_data _add;

	void init();
	char hex(int v) const;
	void single_round();
};

#endif
