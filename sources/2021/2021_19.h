#ifndef __2021_19__
#define __2021_19__

#include "../shared/input_output.h"

namespace Day19_2021
{
	typedef vector<int> t_coords;	// coordinates (x, y, z)

	class Beacon
	{
	public:
		Beacon();
		Beacon(int x, int y, int z);

		int& operator[] (int idx);
		int operator[] (int idx) const;
		bool operator == (const Beacon& rhs);
		bool operator < (const Beacon& rhs) const;

		friend Beacon operator+ (Beacon lhs, const Beacon& rhs);
		friend Beacon operator- (Beacon lhs, const Beacon& rhs);
		
		int manhattan_distance(const Beacon& rhs);

	private:
		t_coords _coords;

		int iabs(int v);
	};

	typedef set<Beacon> t_setBeacon;
	typedef vector<Beacon> t_vecBeacon;
	typedef vector<t_vecBeacon> t_scanners;

	t_output main(const t_input& input);
}

#endif
