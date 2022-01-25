#include "Output.h"

namespace AoC
{
    Output::Output()
    {
    }

    Output::Output(const string& result)
    {
        _lines.push_back(result);
    }

    Output::Output(const pair<string, string>& result)
    {
        _lines.push_back(result.first);
        _lines.push_back(result.second);
    }

    Output::Output(const vector<string>& result)
    {
        _lines.insert(_lines.end(), result.begin(), result.end());
    }

    bool Output::operator != (const Output& other) const
    {
        return _lines != other._lines;
    }

    bool Output::empty() const
    {
        return _lines.size() == 0;
    }
}
