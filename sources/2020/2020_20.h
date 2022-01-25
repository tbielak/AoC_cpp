#ifndef __2020_20__
#define __2020_20__

#include "../shared/Solution.h"

namespace Day20_2020
{
	class Tile;
	typedef vector<Tile*> t_tiles;
	typedef vector<string> t_bitmap;

	class Image
	{
	public:
		Image(const t_bitmap& bitmap);

		int top_edge();
		int right_edge();
		int bottom_edge();
		int left_edge();
		int top_reversed_edge();
		int right_reversed_edge();
		int bottom_reversed_edge();
		int left_reversed_edge();

		void flip_horizontally();
		void flip_vertically();
		void rotate_clockwise();
		void rotate_counterclockwise();

		void release_monsters();
		bool monster_fits_here(size_t x, size_t y);
		void drop_monster(size_t x, size_t y);

		int count_hashes();

		const t_bitmap& bitmap() const { return _bitmap; }

	private:
		size_t _n;
		t_bitmap _bitmap;

		const vector<pair<int, int>> _monster_shape = {
			{ 18, 0 }, { 0, 1 }, { 5, 1 }, { 6, 1 }, { 11, 1 }, { 12, 1 }, { 17, 1 },
			{ 18, 1 }, { 19, 1 }, { 1, 2 }, { 4, 2 }, { 7, 2 }, { 10, 2 }, { 13, 2 }, { 16, 2 } };
		const int _monster_width = 20;
		const int _monster_height = 3;

		int edge_as_int(const string& s);
	};

	class Tile
	{
	public:
		Tile(const string& header, const t_bitmap& bitmap);

		void prepare_edges();
		void match_neighbours(int idx, const t_tiles& tiles);
		
		bool is_corner() const;
		bool is_top_left_corner() const;

		void match_vertically(Tile* ref);
		void match_horizontally(Tile* ref);
		void flip_neighbours_horizontally();
		void flip_neighbours_vertically();
		void rotate_neighbours_clockwise();
		void rotate_neighbours_counterclockwise();

		int id() const { return _id; }
		int right_neighbour() const { return _neighbours[right]; }
		int bottom_neighbour() const { return _neighbours[bottom]; }
		const t_bitmap& bitmap() const { return _image.bitmap(); }

	private:
		int _id;
		Image _image;

		const int top = 0;
		const int right = 1;
		const int bottom = 2;
		const int left = 3;

		vector<int> _edges;
		vector<int> _neighbours;

		int match(int edge, int idx, const t_tiles& tiles);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<t_tiles, size_t> load(const vector<string>& input);
	};
}

#endif
