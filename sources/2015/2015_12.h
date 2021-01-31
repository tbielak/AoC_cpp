#ifndef __2015_12__
#define __2015_12__

#include "../shared/input_output.h"

namespace Day12_2015
{
	// DISCLAIMER:
	// Tiny json parser implemented below (JSONEntity class) covers only
	// a subset of json format. It does not support floating point numbers,
	// boolean and null values, character escaping and whitespaces.
	// Moreover: it cannot detect syntax errors (just crashes).

	enum class JSONEntityKind { ent_unknown, ent_object, ent_array, ent_string, ent_number };

	class JSONEntity;
	typedef vector<JSONEntity*> t_vecJSONEntity;
	typedef pair<string, JSONEntity*> t_JSONPair;
	typedef vector<t_JSONPair> t_JSONObject;

	class JSONEntity
	{
	public:
		JSONEntity();
		~JSONEntity();

		void load(const string& input);

		enum JSONEntityKind kind() const { return _kind; }
		const t_JSONObject& object() const { return _object; }
		const t_vecJSONEntity& array() const { return _array; }
		const string& stringValue() const { return _stringValue; }
		int numberValue() const { return _numberValue; }

	private:
		enum JSONEntityKind _kind;
		t_JSONObject _object;
		t_vecJSONEntity _array;
		string _stringValue;
		int _numberValue;

		size_t load_string(const string& input, string& output, size_t pos);
		size_t load_number(const string& input, int& output, size_t pos);
		size_t load_value(const string& input, size_t pos);
		size_t load_object(const string& input, size_t pos);
		size_t load_array(const string& input, size_t pos);
	};

	t_output main(const t_input& input);
}

#endif
