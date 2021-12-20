#ifndef __2021_14__
#define __2021_14__

#include "../shared/input_output.h"

namespace Day14_2021
{
	typedef map<string, intmax_t> t_polymer;         // pair of chars -> count
	typedef map<string, char> t_rules;               // pair of chars -> target char
	typedef map<char, intmax_t> t_elements;          // char -> count
	typedef map<intmax_t, char> t_elements_rev;      // reversed (count -> char)

	t_output main(const t_input& input);
}

#endif
