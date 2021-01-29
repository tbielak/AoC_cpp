#include "Engine.h"

namespace AoC
{
    Engine::Engine(int year, const t_names& names, const t_repository& repo)
    :   _year(to_string(year)), _names(names), _repo(repo)
    {
    }

    void Engine::intro()
    {
        _cc << "{w}AdventOfCode " + _year + " Puzzle Solutions";
        #ifdef INCLUDE_CUDA
        _cc << " (powered by CUDA)";
        #endif
        _cc << "{d}, copyright(c) 2021 by {y}TomB{d}" << endl;
    }

    void Engine::help()
    {
        _cc << "{y}Available options:{d}" << endl;
        _cc << "{g}-h{d} : help (you are exploring it right now)" << endl;
        _cc << "{g}-c{d} : disable colorful output (useful when streaming to file)" << endl;
        _cc << "{g}-a{d} : show available solutions" << endl;
        _cc << "{g}-p <day>{d} : run solution(s) of selected <day> only (by default all available puzzle solutions are executed)" << endl;
        _cc << "{g}-p <day>:<n>{d} : run n-th solution of puzzle from day <day> (if it is not available, first one is executed)" << endl;
        _cc << "{g}-i <filename>{d} : run with <filename> as input (if not specified inputs are loaded from 'input' directory)" << endl;
        _cc << "{g}-s{d} : execution speed testing (run solutions several times to measure reliable execution time)" << endl;
        _cc << endl;
        _cc << "{y}Warning:{d} Not all combinations of options are supported. See valid ones in examples below:" << endl;
        _cc << "{g}<no options provided>{d} => run everything once, using as input the appropriate files read from 'input' directory" << endl;
        _cc << "{g}-a{d} => show available solutions" << endl;
        _cc << "{g}-p 2{d} => run only the solution(s) of 2nd day puzzle" << endl;
        _cc << "{g}-p 4:2{d} => run 2nd solution of 4th day puzzle" << endl;
        _cc << "{g}-p 5 -i my_input.txt{d} => run 5th day puzzle solution with the input read from my_input.txt file" << endl;
        _cc << "{g}-s{d} => execution speed testing of all puzzles (it may take a while, be patient)" << endl;
        _cc << "{g}-p 7 -s{d} => execution speed testing 7th puzzle solution(s)" << endl;
        _cc << endl;
        _cc << "Enjoy!" << endl;
    }

    void Engine::available_solutions()
    {
        _cc << endl << "{y}Solutions matrix:{d}" << endl;
        _cc << "{g}         1111111111222222{d}" << endl;
        _cc << "{g}1234567890123456789012345{d}  <== day" << endl;

        string solved;
        string solutions;
        for (int i = 1; i <= 25; i++)
        {
            const auto& x = _repo.find(i);
            solved += (x == _repo.end()) ? "-" : to_string(x->second.first);
            solutions += (x == _repo.end()) ? "-" : to_string(x->second.second.size());
        }

        _cc << solved << "  <== parts solved" << endl;
        _cc << solutions << "  <== number of solutions available" << endl;
    }

    bool Engine::load_input(const string& input_filename, size_t i, t_input& input)
    {
        string filename = input_filename;
        if (filename.empty())
        {
            string number = i < 10 ? "0" + to_string(i) : to_string(i);
            filename = "input/" + _year + "_" + number + ".txt";
        }

        string line;
        ifstream f(filename);
        if (!f.is_open())
        {
            _cc << "{r}ERROR: Input file not found!{d}" << endl;
            return false;
        }

        while (getline(f, line))
            input.push_back(line);

        f.close();
        return true;
    }

    void Engine::print_output(const t_output& output, size_t count /* = 0 */)
    {
        for (const auto& x : output.first)
            _cc << x << endl;

        if (count == 0)
            _cc << "Execution time = {y}" << output.second << " ms{d}" << endl;
        else
            _cc << "Average execution time = {y}" << output.second << " ms{d} (executed " << count << " times)" << endl;
    }

    bool Engine::execute(bool print_info, t_output& output, const string& input_filename, int day, size_t solution)
    {
        auto rit = _repo.find(day);
        if (rit == _repo.end())
        {
            if (print_info)
                _cc << "{r}ERROR: Day " << day << " solution(s) are not available.{d}" << endl;

            return false;
        }

        auto& solutions = rit->second.second;
        if (solution >= solutions.size())
        {
            if (print_info)
                _cc << "{r}ERROR: Requested solution is not available.{d}" << endl;

            return false;
        }

        if (print_info)
            _cc << "{g}" << _names.find(day)->second << "{d}" << endl;

        #ifdef INCLUDE_CUDA
        bool CUDA_required = false;
        #endif
        bool execution_possible = true;
        string s = solutions[solution].first;
        if (s != "")
        {
            s = ": " + s;
            size_t pos = s.find("{T}");
            if (pos != string::npos)
            {
                s.erase(pos, 3);
                s.insert(pos, ", " + to_string(thread::hardware_concurrency()) + " concurrent threads");
            }

            #ifdef INCLUDE_CUDA
            pos = s.find("{C}");
            if (pos != string::npos)
            {
                s.erase(pos, 3);
                if (CUDA::cores_total > 0)
                    s.insert(pos, ", " + to_string(CUDA::cores_total) + ", CUDA cores ("
                        + to_string(CUDA::mp) + " multiprocessors * " + to_string(CUDA::cores_mp) + " cores)");

                CUDA_required = true;
            }
            #endif

            if (print_info)
                _cc << "{g}--- Solution #" << int(solution + 1) << s << "{d}" << endl;
        }

        #ifdef INCLUDE_CUDA
        if (CUDA_required && CUDA::cores_total == 0)
        {
            if (print_info)
                _cc << "{r}ERROR: No compatible CUDA devices found!{d}" << endl;

            return false;
        }
        #endif

        t_input input;
        if (!load_input(input_filename, day, input))
            return false;

        output = solutions[solution].second(input);
        return true;
    }

    void Engine::execute_solution(bool speed, const string& input_filename, int day, size_t solution)
    {
        if (speed)
        {
            bool first = true;
            bool ok = false;

            vector<double> time_ms;
            auto t0 = chrono::steady_clock::now();

            t_output ref, output;
            while (1)
            {
                output = t_output();
                ok = execute(first, output, input_filename, day, solution);
                if (!ok)
                    break;

                if (first)
                    ref = output;
                else
                {
                    if (ref.first != output.first)
                    {
                        _cc << "{r}ERROR: Different results obtained in {d}" << endl;
                        break;
                    }
                }

                time_ms.push_back(output.second);
                auto t1 = chrono::steady_clock::now();
                double time_elapsed = chrono::duration<double>((t1 - t0) * 1000).count();

                if (time_elapsed >= 5000. && time_ms.size() >= 5)
                {
                    sort(time_ms.begin(), time_ms.end());
                    double v = 0.;
                    for (size_t i = 1; i < time_ms.size() - 1; i++)
                        v += time_ms[i];

                    output.second = v / (time_ms.size() - 2);
                    break;
                }

                first = false;
            }

            if (ok)
                print_output(output, time_ms.size());

            if (!ok && !first)
                _cc << "{r}ERROR: Unable to run speed test{d}" << endl;
        }
        else
        {
            t_output output;
            if (execute(true, output, input_filename, day, solution))
                print_output(output);
        }
    }

    void Engine::execute_day(bool speed, const string& input_filename, int day)
    {
        auto rit = _repo.find(day);
        if (rit == _repo.end())
        {
            _cc << "{r}ERROR: Day " << day << " solution(s) are not available.{d}" << endl;
            return;
        }

        auto& solutions = rit->second.second;
        for (size_t sol = 0; sol < solutions.size(); sol++)
            execute_solution(speed, input_filename, day, sol);
    }

    void Engine::execute_all(bool speed)
    {
        for (const auto& puzzle : _repo)
        {
            const auto& [day, solutions] = puzzle;
            for (size_t sol = 0; sol < solutions.second.size(); sol++)
                execute_solution(speed, "", day, sol);
        }
    }

    int Engine::run(int argc, char* argv[])
    {
        AoC::Options opt;
        opt.parse(argc, argv);
        if (!opt.colors)
            _cc.disable_colors();

        _cc.setup();
        intro();

        if (opt.help)
        {
            help();
            return 0;
        }

        #ifdef INCLUDE_CUDA
        CUDA::setup(_cc);
        #endif

        if (opt.available)
        {
            available_solutions();
            return 0;
        }

        if (opt.speed)
        {
            _cc << "{y}Warning:{d} In this mode ({g}-s{d}) each puzzle solution is run at least five times and at least for five seconds." << endl;
            _cc << "It may take some time to obtain all results, please be patient. The highest and the lowest time measurements" << endl;
            _cc << "are dropped, the average time of all remaining is printed. Repeatability of results is checked after each execution." << endl;
        }

        if (opt.day > -1)
        {
            if (opt.solution > -1)
                execute_solution(opt.speed, opt.input_filename, opt.day, opt.solution);
            else
                execute_day(opt.speed, opt.input_filename, opt.day);
        }
        else
            execute_all(opt.speed);

        return 0;
    }
}
