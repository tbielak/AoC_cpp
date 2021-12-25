#include "2021_19.h"

namespace Day19_2021
{
	Beacon::Beacon()
	:	_coords(t_coords(3, 0))
	{
	}

	Beacon::Beacon(int x, int y, int z)
	:	_coords({ x, y, z })
	{
	}

	int& Beacon::operator[] (int idx)
	{
		return _coords[idx];
	}

	int Beacon::operator[] (int idx) const
	{
		return _coords[idx];
	}
		
	bool Beacon::operator == (const Beacon& rhs)
	{
		return _coords == rhs._coords;
	}

	bool Beacon::operator < (const Beacon& rhs) const
	{
		if (_coords[0] == rhs._coords[0])
		{
			if (_coords[1] == rhs._coords[1])
				return _coords[2] < rhs._coords[2];

			return _coords[1] < rhs._coords[1];
		}

		return _coords[0] < rhs._coords[0];
	}

	Beacon operator+ (Beacon lhs, const Beacon& rhs)
	{
		lhs._coords[0] += rhs._coords[0];
		lhs._coords[1] += rhs._coords[1];
		lhs._coords[2] += rhs._coords[2];
		return lhs;
	}

	Beacon operator- (Beacon lhs, const Beacon& rhs)
	{
		lhs._coords[0] -= rhs._coords[0];
		lhs._coords[1] -= rhs._coords[1];
		lhs._coords[2] -= rhs._coords[2];
		return lhs;
	}
	
	int Beacon::manhattan_distance(const Beacon& rhs)
	{
		return iabs(_coords[0] - rhs._coords[0])
			+ iabs(_coords[1] - rhs._coords[1])
			+ iabs(_coords[2] - rhs._coords[2]);
	}

	int Beacon::iabs(int v)
	{
		return (v < 0) ? -v : v;
	}

	static const vector<vector<int>> orientation_swap =
	{
		{0, 1, 2}, {0, 2, 1}, {0, 1, 2}, {0, 2, 1},
		{1, 2, 0}, {1, 0, 2}, {1, 2, 0}, {1, 0, 2},
		{2, 0, 1}, {2, 1, 0}, {2, 0, 1}, {2, 1, 0},
		{0, 2, 1}, {0, 1, 2}, {0, 2, 1}, {0, 1, 2},
		{1, 0, 2}, {1, 2, 0}, {1, 0, 2}, {1, 2, 0},
		{2, 1, 0}, {2, 0, 1}, {2, 1, 0}, {2, 0, 1}
	};

	static const vector<vector<int>> orientation_sign =
	{
		{1, 1, 1}, {1, -1, 1}, {1, -1, -1}, {1, 1, -1},
		{1, 1, 1}, {1, -1, 1}, {1, -1, -1}, {1, 1, -1},
		{1, 1, 1}, {1, -1, 1}, {1, -1, -1}, {1, 1, -1},
		{-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1},
		{-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1},
		{-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}
	};

	t_vecBeacon get_orientation(const t_vecBeacon& ref, int idx)
	{
		t_vecBeacon result = t_vecBeacon(ref.size());
		for (int i = 0; i < (int)ref.size(); i++)
			for (int c = 0; c < 3; c++)
				result[i][c] = orientation_sign[idx][c] * ref[i][orientation_swap[idx][c]];

		return result;
	}

	pair<int, int> both_parts(t_scanners& scanners)
	{
		// create set of reference points
		// get all beacon points from reference scanner (0th)
		t_setBeacon reference(scanners[0].begin(), scanners[0].end());

		// known scanner positions, relative to reference scanner
		// reference scanner position is not included here, it is (0,0,0)
		t_vecBeacon scanner_positions;
		
		// queue of scanners to analyze
		queue<size_t> queue;
		for (size_t i = 1; i < scanners.size(); i++)
			queue.push(i);

		// one by one
		while (!queue.empty())
		{
			// current scanner to analyze
			size_t current_idx = queue.front();
			const t_vecBeacon& sc = scanners[current_idx];
			queue.pop();

			// trying to find one of 24 orientations
			// having as many overlapped beacon positions as possible
			// (between reference and current scanner)
			int good_orientation_index = -1;

			// trying to find scanner position
			Beacon position;

			// through orientations...
			for (int oidx = 0; oidx < 24; oidx++)
			{
				// get current scanner beacon points in selected orientation
				t_vecBeacon current = get_orientation(sc, oidx);

				// subtract every two points of reference and current -> make Cartesian product
				// and count how many times different result occures
				map<Beacon, int> subs;
				for (const auto& ref : reference)
					for (const auto& cur : current)
						subs[ref - cur]++;

				// finding overlaps:
				// count how many times different result occured
				map<int, int> counts;
				for (const auto& s : subs)
					counts[s.second]++;

				// explore counts map in reverse order (we're interested in high values)
				for (map<int, int>::const_reverse_iterator it = counts.rbegin(); it != counts.rend(); it++)
				{
					// less than 12 beacon positions overlaping? -> no solution for now
					if (it->first < 12)
						break;
					
					// find overlaping value -> this is scanner position!
					for (const auto& x : subs)
						if (x.second == it->first)
							position = x.first;

					// remember current orientation, finish searching
					good_orientation_index = oidx;
					break;
				}

				// we already found solution -> break
				if (good_orientation_index != -1)
					break;
			}

			// if solution is not found...
			if (good_orientation_index == -1)
			{
				// ...put current scanner to the back of the queue
				// to re-analyze it later, when reference set will be larger
				queue.push(current_idx);
				continue;
			}

			// get current scanner in correct orientation
			t_vecBeacon correct = get_orientation(sc, good_orientation_index);

			// get all beacon points of current scanner as seen from reference scanner perspective
			// and add them into set of reference points
			for (const auto& x : correct)
				reference.insert(x + position);

			// store known scanner position
			scanner_positions.push_back(position);
		}

		// get largest Manhattan distance between any two scanners
		int distance = 0;
		for (size_t i = 0; i < scanner_positions.size(); i++)
			for (size_t j = 0; j < scanner_positions.size(); j++)
				if (i != j)
				{
					int d = scanner_positions[i].manhattan_distance(scanner_positions[j]);
					distance = max(distance, d);
				}

		// return result
		return make_pair((int)reference.size(), distance);
	}

	t_output main(const t_input& input)
	{
		t_scanners scanners;
		scanners.push_back(t_vecBeacon());
		for (size_t i = 0; i < input.size(); i++)
		{
			if (input[i] == "")
				scanners.push_back(t_vecBeacon());
			else
				if (input[i].substr(0, 3) != "---")
				{
					smatch matches;
					regex regex("([-|0-9]*),([-|0-9]*),([-|0-9]*)");
					regex_search(input[i], matches, regex);
					scanners.back().push_back(Beacon(stoi(matches[1]), stoi(matches[2]), stoi(matches[3])));
				}
		}

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(scanners);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
