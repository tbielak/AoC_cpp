#include "2019_20.h"

namespace Day20_2019
{
	Position::Position(int row /* = 0 */, int col /* = 0 */)
	:	row(row), col(col)
	{
	}
	
	bool Position::operator < (const Position& other) const
	{
		return (row == other.row) ? col < other.col : row < other.row;
	}

	bool Position::operator == (const Position& other) const
	{
		return row == other.row && col == other.col;
	}

	bool Position::operator != (const Position& other) const
	{
		return row != other.row || col != other.col;
	}

	const vector<Position> Position::update = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	Target::Target()
	:	inner(false)
	{
	}

	Target::Target(const string& id, bool inner)
	:	id(id), inner(inner)
	{
	}

	Route::Route(int length, const Position& target, int level_change)
	:	length(length), target(target), level_change(level_change)
	{
	}

	Labyrinth::Labyrinth(const vector<string>& input)
	{
		// load from input
		_labyrinth = input;

		// scan labyrinth, find positions of teleports, replace letters 'A'..'Z' in labyrinth
		// by walls ('#') and spaces (' '); mark teleports as '@' (see add_teleport method below)
		string id = "??";
		int height = (int)_labyrinth.size();
		int width = (int)_labyrinth[0].size();
		for (int row = 0; row < height - 1; row++)
			for (int col = 0; col < width - 1; col++)
			{
				if (!isalpha(_labyrinth[row][col]))
					continue;

				if (isalpha(_labyrinth[row + 1][col]))
				{
					// vertical teleport
					id[0] = _labyrinth[row][col];
					id[1] = _labyrinth[row + 1][col];
					bool inner = (row > 0) && (row < height - 2);
					
					if (row == 0 || (row < height - 2 && _labyrinth[row + 2][col] == '.'))
						add_teleport(row, col, row + 1, col, row + 2, col, id, inner);
					else
						add_teleport(row + 1, col, row, col, row - 1, col, id, inner);
				}
				else
				{
					// horizontal teleport
					id[0] = _labyrinth[row][col];
					id[1] = _labyrinth[row][col + 1];
					bool inner = (col > 0) && (col < width - 2);
					
					if (col == 0 || (col < width - 2 && _labyrinth[row][col + 2] == '.'))
						add_teleport(row, col, row, col + 1, row, col + 2, id, inner);
					else
						add_teleport(row, col + 1, row, col, row, col - 1, id, inner);
				}
			}

		// assign teleport target positions
		for (auto& src : _teleports)
			for (const auto& dst : _teleports)
				if (src.first != dst.first && src.second.id == dst.second.id)
					src.second.position = dst.first;
	}

	void Labyrinth::add_teleport(int empty_row, int empty_col, int wall_row, int wall_col, int teleport_row, int teleport_col, const string& id, bool inner)
	{
		_labyrinth[empty_row][empty_col] = ' ';
		_labyrinth[wall_row][wall_col] = '#';
		_labyrinth[teleport_row][teleport_col] = '@';
		
		Position p(teleport_row, teleport_col);
		_teleports[p] = Target(id, inner);
		
		if (id == "AA")
			_start = p;

		if (id == "ZZ")
			_finish = p;
	}

	// BFS: find all routes from source position to any teleport reachable on the same level
	t_routes Labyrinth::bfs_find_routes(const Position& source)
	{
		// result
		t_routes routes;

		// visited places
		set<Position> visited;
		visited.insert(source);

		// queue of positions to examine with steps already done
		queue< pair<Position, int> > queue;
		queue.push(make_pair(source, 1));

		// go through the labyrinth
		while (!queue.empty())
		{
			// current position and number of steps
			auto [position, steps] = queue.front();
			queue.pop();

			// four possible moves
			for (int i = 0; i < 4; i++)
			{
				// next position
				Position next(position.row + Position::update[i].row, position.col + Position::update[i].col);

				// should be an open passage, not visited yet
				if (_labyrinth[next.row][next.col] == '.' && visited.find(next) == visited.end())
				{
					// go there
					queue.push(make_pair(next, steps + 1));
					visited.insert(next);
				}

				// if not visited teleport...
				if (_labyrinth[next.row][next.col] == '@' && visited.find(next) == visited.end())
				{
					// ...new route is found!
					const auto& t = _teleports.find(next);
					routes.push_back(Route(steps, t->first, t->second.inner ? 1 : -1));
				}
			}
		}

		return routes;
	}

	// recursively find route (using teleports) from _start to _finish:
	// - on the same level (when level_coeff = 0), or:
	// - on recursive spaces = different levels (when level_coeff = 1)
	// while exploring: do not use more than max_teleports teleports (to avoid infinite loops) and find shortest path (min_steps)
	// position and level -> current position and current level on recursive re-entry of the method
	void Labyrinth::recursive_find(const t_paths& paths, Position position, int teleports_used, int max_teleports, int level, int level_coeff, int steps, int& min_steps)
	{
		// go through all possible routes from current position
		const t_routes& all_routes = paths.find(position)->second;
		for (const auto& route : all_routes)
		{
			// when route target is finish...
			if (route.target == _finish)
			{
				// ... and level zero: check if shortest path found (so far)
				if (level == 0)
					min_steps = min(min_steps, steps + route.length);
			}
			else
			// if not going back to start...
			if (route.target != _start)
			{
				// ...calculate parameters for next recursion...
				int next_level = level + route.level_change * level_coeff;
				int next_steps = steps + route.length + 1;

				// ...and do it under some conditions:
				if (next_level >= 0 && next_steps < min_steps && teleports_used < max_teleports)
				{
					recursive_find(paths, _teleports.find(route.target)->second.position,
						teleports_used + 1, max_teleports, next_level, level_coeff, next_steps, min_steps);
				}
			}
		}
	}
	
	// walking from _start to _finish (on the same level or on different levels, depending on recursive_spaces value)
	int Labyrinth::walk_through_levels(bool recursive_spaces)
	{
		// find all paths from every teleport to every other one, on the same level
		t_paths paths;
		for (const auto& source : _teleports)
		{
			auto [position, teleport] = source;
			if (teleport.id != "ZZ")
				paths[position] = bfs_find_routes(position);
		}

		// set big min_steps
		int min_steps = INT_MAX;

		// set maximum number of teleports used (to avoid infinite loops)
		// WARNING! this is crucial parameter and the weakest point of the algorith used:
		// - when obtaining -1 (meaning: no solution) or incorrect result -> increase it a bit
		// - do not increase it a lot, 'cause you really have no time to wait for it :)
		// anyway: it should work with the value provided below ;)
		int max_teleports = int(_teleports.size() + _labyrinth.size());

		// recursively find solution
		recursive_find(paths, _start, 0, max_teleports, 0, recursive_spaces ? 1 : 0, 0, min_steps);
		return min_steps == INT_MAX ? -1 : min_steps;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Labyrinth(input).walk_through_levels(false);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Labyrinth(input).walk_through_levels(true);
	}
}
