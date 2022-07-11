#ifndef __2017_18__
#define __2017_18__

#include "../shared/Solution.h"

namespace Day18_2017
{
	class Argument
	{
	public:
		Argument(const string& s = "0");

		bool imm;
		char reg;
		int64_t val;
	};

	enum class Operation { op_set, op_add, op_mul, op_mod, op_jgz, op_snd, op_rcv };

	class Instruction
	{
	public:
		Instruction(const string& input);

		Operation op;
		Argument dst, src;

	private:
		static map<string, Operation> _map;
	};

	typedef vector<Instruction> t_program;

	class CPU
	{
	public:
		CPU();
		void load(CPU* other, const t_program& program, int pvalue);

		bool step();

		int64_t snd_count() const { return _snd_count; }
		int64_t queue_back() const { return _queue.back(); }

	private:
		CPU* _other;
		t_program _program;
		size_t _pc;
		map<char, int64_t> _regs;
		queue<int64_t> _queue;
		int64_t _snd_count;

		int64_t get(const Argument& x);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_program load(const vector<string>& input);
	};
}

#endif
