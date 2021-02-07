#ifndef __2020_16__
#define __2020_16__

#include "../shared/input_output.h"

namespace Day16_2020
{
	typedef pair<int, int> t_range;

	class Property
	{
	public:
		Property(const string& name, const t_range& r1, const t_range& r2);

		string name;
		t_range r1;
		t_range r2;
		bool isDeparture;
	};

	typedef vector<Property> t_vecProperty;

	class Ticket
	{
	public:
		Ticket(const string& input);

		auto size() const { return _data.size(); }
		auto& operator [] (size_t idx) const { return _data[idx]; }

	private:
		vector<int> _data;
	};

	typedef vector<Ticket> t_vecTicket;

	class MatchMatrix
	{
	public:
		MatchMatrix(size_t columnCount, size_t propertyCount, int initValue);

		void set(size_t columnIdx, size_t propertyIdx);
		void reduce(MatchMatrix& other);
		void find(size_t& columnIndex, size_t& propertyIndex);
		void reduce(size_t propertyIdx);

	private:
		typedef vector<int> t_vecProperty;
		typedef vector<t_vecProperty> t_vecMatrix;
		size_t _columnCount;
		size_t _propertyCount;
		t_vecMatrix _matrix;
	};

	t_output main(const t_input& input);
}

#endif
