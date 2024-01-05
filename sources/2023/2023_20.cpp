#include "2023_20.h"

namespace Day20_2023
{
	class Module
	{
	public:
		Module()
		:	type('=') // output
		{
		}

		Module(const string& input)
		{
			size_t pos = input.find(" -> ");
			name = input.substr(0, pos);

			size_t offset = pos + 4;
			while (pos != string::npos)
			{
				pos = input.find_first_of(',', offset);
				dest.push_back(input.substr(offset, pos - offset));
				offset = pos + 2;
			}

			if (name == "broadcaster")
				type = '!';
			else
			{
				type = name[0];
				name = name.substr(1);
			}
		}

		pair<bool, bool> process(const string& input_name, bool signal)	// true = high
		{
			if (type == '%') // Flip-flop module
			{
				if (signal)
					return { true, signal };	// ignore result

				state = !state;
				return { false, state };	// do not ignore, state returned
			}

			if (type == '&') // Conjunction module
			{
				mrp[input_name] = signal;

				bool all = true;
				for (const auto [_, v] : mrp)
					all &= v;

				return { false, !all };		// do not ignore, !all returned
			}

			return { true, signal };	// ignore result
		}

		char type;	// %, &, ! or = (Flip-flop, Conjunction, Broadcaster, Output)
		string name;
		vector<string> dest;

		bool state = false;	// state (of Flip-flop module = '%')
		map<string, bool> mrp; // most-recent-pulse received from other modules (of Conjunction module = '&')
	};

	map<string, Module*> load(const vector<string>& input)
	{
		map<string, Module*> modules;
		for (const auto& s : input)
		{
			Module* m = new Module(s);
			modules[m->name] = m;
		}

		return modules;
	}

	void initialize_mrp(map<string, Module*>& modules)
	{
		for (auto& [n, m] : modules)
			if (m->type == '&')
				for (const auto& [sn, sm] : modules)
					for (const auto& s : sm->dest)
						if (s == n)
							m->mrp[sn] = false;
	}

	Module* find_broadcaster(map<string, Module*>& modules)
	{
		for (auto& m : modules)
			if (m.second->type == '!')
				return m.second;

		return nullptr;
	}

	void press_button(int i, map<string, Module*>& modules, map<string, int>& targets, int& low, int& high)
	{
		low++;	// low from Broadcaster
		queue<pair<Module*, bool>> pulses;
		pulses.push(make_pair(find_broadcaster(modules), false));

		while (!pulses.empty())
		{
			auto [src_module, signal] = pulses.front();
			pulses.pop();

			for (const string& name : src_module->dest)
			{
				if (signal) high++; else low++;

				Module* m = nullptr;
				auto it = modules.find(name);
				if (it != modules.end())
					m = it->second;
				else
				{
					m = new Module(name);
					modules[name] = m;
				}

				auto [ignored, result] = m->process(src_module->name, signal);
				if (!ignored)
					pulses.push(make_pair(m, result));

				if (signal)
				{
					auto nit = targets.find(src_module->name);
					if (nit != targets.end())
						targets[src_module->name] = i;
				}
			}
		}
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		auto modules = load(input);
		initialize_mrp(modules);

		// --> specific input, see graph here: https://github.com/tbielak/AoC_cpp/blob/master/doc/2023_20.svg
		//
		// Observations:
		// - there is one Conjunction module which is the source for "rx" - module named "mf"
		// - there are four Conjunction modules which are the source for "mf" - modules named "sh", "jf", "bh", "mz"
		// - due to Conjunction module behaviour and due to linking shown above we need to find the moment when
		//   "sh", "jf", "bh", "mz" modules receive 'high' signal during the same button press
		// - we can observe them separately (see targets map below), and when the number of pushes needed
		//   to receive 'high' signal is available for each of them, we can multiply number of pushes
		//   to find the final result (prime numbers, multiplying is ok)
		vector<string> important_modules;
		important_modules.push_back("rx");
		for (int i = 0; i < 2; i++)
		{
			vector<string> names;
			for (const auto& [n, m] : modules)
				for (const auto& s : m->dest)
					for (const auto& i : important_modules)
						if (s == i)
							names.push_back(n);

			important_modules = move(names);
		}

		map<string, int> targets;
		for (const auto& s : important_modules)
			targets[s] = 0;
		// <-- assumptions related to specific input end here

		int low = 0;
		int high = 0;
		int64_t part_one_result = 0;
		for (int i = 1; ; i++)
		{
			press_button(i, modules, targets, low, high);
			if (i == 1000)
				part_one_result = low * high;

			bool done = true;
			for (const auto& [_, v] : targets)
				if (v == 0)
					done = false;

			if (done)
				break;
		}

		int64_t part_two_result = 1;
		for (const auto& [_, v] : targets)
			part_two_result *= int64_t(v);	// assuming prime numbers

		return make_pair(part_one_result, part_two_result);
	}
}
