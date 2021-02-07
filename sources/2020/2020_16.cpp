#include "2020_16.h"

namespace Day16_2020
{
	Property::Property(const string& name, const t_range& r1, const t_range& r2)
	:	name(name), r1(r1), r2(r2)
	{
		isDeparture = name.find("departure") != string::npos;
	}

	Ticket::Ticket(const string& input)
	{
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			_data.push_back(stoi(s));
	}

	int part_one(const t_vecProperty& properties, const t_vecTicket& nearbyTickets)
	{
		int errorRate = 0;
		size_t propertyCount = properties.size();
		size_t columnCount = nearbyTickets[0].size();

		for (const auto& ticket : nearbyTickets)
		{
			for (size_t c = 0; c < columnCount; c++)
			{
				int x = ticket[c];
				bool valid = false;
				for (size_t p = 0; p < propertyCount; p++)
				{
					if ((x >= properties[p].r1.first && x <= properties[p].r1.second) ||
						(x >= properties[p].r2.first && x <= properties[p].r2.second))
						valid = true;
				}

				if (!valid)
					errorRate += x;
			}
		}

		return errorRate;
	}

	MatchMatrix::MatchMatrix(size_t columnCount, size_t propertyCount, int initValue)
	:	_columnCount(columnCount), _propertyCount(propertyCount)
	{
		t_vecProperty p(propertyCount, initValue);
		_matrix = t_vecMatrix(columnCount, p);
	}

	void MatchMatrix::set(size_t columnIdx, size_t propertyIdx)
	{
		_matrix[columnIdx][propertyIdx] = 1;
	}

	void MatchMatrix::reduce(MatchMatrix& other)
	{
		for (size_t c = 0; c < _columnCount; c++)
		{
			vector<size_t> noMatch;
			for (size_t p = 0; p < _columnCount; p++)
				if (other._matrix[c][p] == 0)
					noMatch.push_back(p);

			for (auto p : noMatch)
				_matrix[c][p] = 0;
		}
	}

	void MatchMatrix::find(size_t& columnIndex, size_t& propertyIndex)
	{
		for (size_t c = 0; c < _columnCount; c++)
		{
			int cnt = 0;
			for (size_t p = 0; p < _propertyCount; p++)
				if (_matrix[c][p] == 1)
					cnt++;

			if (cnt == 1)
			{
				for (size_t p = 0; p < _propertyCount; p++)
					if (_matrix[c][p] == 1)
						propertyIndex = p;

				columnIndex = c;
				return;
			}
		}

		throw runtime_error("omg, no reliable match!");
	}

	void MatchMatrix::reduce(size_t propertyIdx)
	{
		for (size_t c = 0; c < _columnCount; c++)
			_matrix[c][propertyIdx] = 0;
	}

	long long int part_two(const t_vecProperty& properties, const t_vecTicket& nearbyTickets, const Ticket& myTicket)
	{
		size_t propertyCount = properties.size();
		size_t columnCount = myTicket.size();

		// assume all data match all properties
		MatchMatrix finalMatch(columnCount, propertyCount, 1);

		for (const auto& ticket : nearbyTickets)
		{
			bool ticketValid = true;
			MatchMatrix valueMatch(columnCount, propertyCount, 0);		// no matches
			for (size_t c = 0; c < columnCount; c++)
			{
				bool anyMatch = false;
				for (size_t p = 0; p < propertyCount; p++)
				{
					int x = ticket[c];
					if ((x >= properties[p].r1.first && x <= properties[p].r1.second) ||
						(x >= properties[p].r2.first && x <= properties[p].r2.second))
					{
						anyMatch = true;
						valueMatch.set(c, p);		// value in column c matches property p
					}
				}

				if (!anyMatch)
					ticketValid = false;
			}

			if (!ticketValid)
				continue;

			// reduce finalMatch basing on valueMatch
			finalMatch.reduce(valueMatch);
		}

		// assigning properties indices to columns of data
		vector<size_t> data2property(columnCount);
		for (size_t c = 0; c < propertyCount; c++)
		{
			size_t columnIdx, propertyIdx;
			finalMatch.find(columnIdx, propertyIdx);	// find column to property match
			data2property[columnIdx] = propertyIdx;
			finalMatch.reduce(propertyIdx);				// remove property allowing next match
		}

		// find departures
		long long int value = 1;
		for (size_t c = 0; c < columnCount; c++)
		{
			if (properties[data2property[c]].isDeparture)
				value *= myTicket[c];
		}

		return value;
	}

	t_output main(const t_input& input)
	{
		// loading properties
		regex regex("([ a-z]*): ([0-9]*)-([0-9]*) or ([0-9]*)-([0-9]*)");
		smatch matches;
		t_vecProperty properties;
		size_t idx = 0;
		for (; idx < input.size(); idx++)
		{
			if (input[idx].empty())
				break;

			regex_search(input[idx], matches, regex);

			properties.push_back(
				Property(matches[1].str(),
					make_pair(stoi(matches[2].str()), stoi(matches[3].str())),
					make_pair(stoi(matches[4].str()), stoi(matches[5].str()))));
		}

		// loading my ticket
		for (; idx < input.size(); idx++)
			if (input[idx] == "your ticket:")
				break;

		idx++;
		Ticket myTicket(input[idx++]);

		// loading nearby tickets
		for (; idx < input.size(); idx++)
			if (input[idx] == "nearby tickets:")
				break;

		idx++;
		t_vecTicket nearbyTickets;
		for (; idx < input.size(); idx++)
			nearbyTickets.push_back(Ticket(input[idx]));

		// solve
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(properties, nearbyTickets);
		auto p2 = part_two(properties, nearbyTickets, myTicket);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
