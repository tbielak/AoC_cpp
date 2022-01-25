#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "stl.h"

namespace AoC
{
    class Output
    {
    public:
        friend class Engine;
        friend class Solution;

        Output();
        Output(const string& result);
        Output(const pair<string, string>& result);
        Output(const vector<string>& result);
        
        template <typename T>
        Output(T result)
        {
            _lines.push_back(to_string(result));
        }

        template <typename T>
        Output(const pair<T, T>& result)
        {
            _lines.push_back(to_string(result.first));
            _lines.push_back(to_string(result.second));
        }

        template <typename T>
        Output(const vector<T>& result)
        {
            for (auto x : result)
                _lines.push_back(to_string(x));
        }

        bool operator != (const Output& other) const;
        bool empty() const;

    private:
        vector<string> _lines;
    };
}

#endif
