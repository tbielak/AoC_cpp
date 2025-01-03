#include "2023_22.h"

namespace Day22_2023
{
	Point3D::Point3D()
	:	x(0), y(0), z(0)
	{
	}

	Point3D::Point3D(const string& s)
	{
		smatch matches;
		regex regex("([0-9]*),([0-9]*),([0-9]*)");
		regex_search(s, matches, regex);
		x = stoi(matches[1]);
		y = stoi(matches[2]);
		z = stoi(matches[3]);
	}

	Cell::Cell(int id /* = -1 */, int plane /* = PLANE_UNDEFINED */)
	:	id(id), plane(plane)
	{
	}

	int Main::fall(t_cuboid& cuboid, const Point3D& size, int remove /* = INT_MIN */)
	{
		int fallen = 0;		// number of bricks which have fallen a bit
		set<int> checked;	// set of bricks already checked and/or moved

		// scan cuboid from bottom to top
		for (int z = 1; z < size.z; z++)
			for (int y = 0; y < size.y; y++)
				for (int x = 0; x < size.x; x++)
				{
					// skip empty cells
					auto c = cuboid[z][y][x];
					if (c.id == -1)
						continue;

					// skip cells which are part of bricks already checked and/or moved
					if (checked.find(c.id) != checked.end())
						continue;

					checked.insert(c.id);

					// skip bricks already touching bottom
					if (z == 1)
						continue;

					// try to move down a brick according to its plane
					switch (c.plane)
					{
					case PLANE_YZ:
					{
						// check if all cells of this brick can fall
						bool can_fall = true;
						int nx = x;
						while (nx < size.x && cuboid[z][y][nx].id == c.id)
						{
							// empty cell or removed cell below?
							can_fall &= (cuboid[z - 1][y][nx].id == -1 || cuboid[z - 1][y][nx].id == remove);
							nx++;
						}

						if (can_fall)
						{
							// move down
							nx = x;
							while (nx < size.x && cuboid[z][y][nx].id == c.id)
							{
								cuboid[z - 1][y][nx] = cuboid[z][y][nx];
								cuboid[z][y][nx] = Cell();
								nx++;
							}

							fallen++;
						}

						break;
					}

					case PLANE_XZ:
					{
						// check if all cells of this brick can fall
						bool can_fall = true;
						int ny = y;
						while (ny < size.y && cuboid[z][ny][x].id == c.id)
						{
							// empty cell or removed cell below?
							can_fall &= (cuboid[z - 1][ny][x].id == -1 || cuboid[z - 1][ny][x].id == remove);
							ny++;
						}

						if (can_fall)
						{
							// move down
							ny = y;
							while (ny < size.y && cuboid[z][ny][x].id == c.id)
							{
								cuboid[z - 1][ny][x] = cuboid[z][ny][x];
								cuboid[z][ny][x] = Cell();
								ny++;
							}

							fallen++;
						}

						break;
					}

					case PLANE_XY:
					{
						// empty cell or removed cell below?
						if (cuboid[z - 1][y][x].id == -1 || cuboid[z - 1][y][x].id == remove)
						{
							// move down
							int nz = z;
							while (nz < size.z && cuboid[nz][y][x].id == c.id)
							{
								cuboid[nz - 1][y][x] = cuboid[nz][y][x];
								cuboid[nz][y][x] = Cell();
								nz++;
							}

							fallen++;
						}

						break;
					}
					}
				}

		// return number of fallen bricks
		return fallen;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// load bricks = pairs of 3D points
		vector<pair<Point3D, Point3D>> bricks;
		for (const string& s : input)
		{
			size_t pos = s.find('~');
			bricks.push_back(make_pair(Point3D(s.substr(0, pos)), Point3D(s.substr(pos + 1))));
		}

		// determine the size of the cuboid in which the blocks fall
		Point3D size;
		for (const auto [p1, p2] : bricks)
		{
			// in the meantime: check the assumptions, if not satisfied -> panic with (-1, -1) pair = no solution
			if (p1.x > p2.x || p1.y > p2.y || p1.z > p2.z || p1.x < 0 || p1.y < 0 || p1.z < 0)
				return make_pair(-1, -1);

			size.x = max(size.x, p2.x);
			size.y = max(size.y, p2.y);
			size.z = max(size.z, p2.z);
		}
		size.x++;
		size.y++;
		size.z++;

		// create empty cuboid
		t_cuboid cuboid = t_cuboid(size.z, vector<vector<Cell>>(size.y, vector<Cell>(size.x)));

		// place bricks inside cuboid, set id and plane of each cuboid
		int maxid = 0;
		for (const auto [p1, p2] : bricks)
		{
			int plane = PLANE_UNDEFINED;
			if (p1.y == p2.y && p1.z == p2.z) plane = PLANE_YZ;
			if (p1.x == p2.x && p1.z == p2.z) plane = PLANE_XZ;
			if (p1.x == p2.x && p1.y == p2.y) plane = PLANE_XY;

			// the algorithm handles only cuboids laying on these planes, otherwise -> panic with (-1, -1) = no solution
			if (plane == PLANE_UNDEFINED)
				return make_pair(-1, -1);

			for (int z = p1.z; z <= p2.z; z++)
				for (int y = p1.y; y <= p2.y; y++)
					for (int x = p1.x; x <= p2.x; x++)
						cuboid[z][y][x] = Cell(maxid, plane);

			maxid++;
		}

		// settle down all the bricks
		while (fall(cuboid, size) > 0);

		// try to remove one by one and count how many bricks can fall
		auto copy = cuboid;
		vector<int> count = vector<int>(maxid);
		for (int id = 0; id < maxid; id++)
		{
			cuboid = copy;
			count[id] = fall(cuboid, size, id);
		}

		// sum results to obtain both parts solution
		int p1 = 0;
		int p2 = 0;
		for (auto c : count)
		{
			if (c == 0) p1++;
			p2 += c;
		}

		return make_pair(p1, p2);
	}
}
