#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace flyweight {

struct HeavyweightTextFormatter {
  string plain_text;
  vector<bool> capitalized;

  HeavyweightTextFormatter(const string &plain_text)
      : plain_text(plain_text) {
    for (int i = 0; i < plain_text.length(); ++i)
      capitalized.push_back(false);
  }

  void Capitalize(unsigned int start, unsigned int end) {
    for (unsigned int i = start; i <= end; ++i)
      capitalized[i] = true;
  }

  string Capitalize() const {
    string str;
    for (unsigned int i = 0; i < plain_text.length(); ++i) {
      char ch = plain_text[i];
      str += (capitalized[i] ? toupper(ch) : ch);
    }
    return str;
  }

  friend ostream &operator<<(ostream &os, const HeavyweightTextFormatter &obj) {
    return os << obj.Capitalize();
  }
};

struct LightweightTextFormatter
{
  struct TextRange
  {
    unsigned int start, end;
    bool capitalize, bold, italic;

    bool Covers(unsigned int position) const
    {
      return start <= position && position <= end;
    }

    bool operator<(const TextRange& obj) const
    {
      return obj.start < start && obj.end < end;
    }
  };

  string plain_text;
  vector<TextRange> fmt_ranges;

  LightweightTextFormatter(const string &plain_text) : plain_text(plain_text) {}

  TextRange& Range(unsigned int start, unsigned end)
  {
    auto it = find_if(
        fmt_ranges.begin(),
        fmt_ranges.end(),
        [&](const TextRange& lhs) {
          return lhs.start == start && lhs.end == end;
        });
    // 1: do not include duplicated ranges
    // 2: do not handle ranges overlaps
    if (it == fmt_ranges.end()) fmt_ranges.emplace_back(TextRange{start, end});

    return *fmt_ranges.rbegin();
  }

  string Capitalize() const
  {
    string str;

    for (unsigned int i = 0; i < plain_text.length(); ++i)
    {
      char ch = plain_text[i];
      for (const auto& text : fmt_ranges)
      {
        if (text.capitalize && text.Covers(i)) ch = toupper(ch);
      }
      str += ch;
    }

    return str;
  }

  friend ostream& operator<<(ostream& os, const LightweightTextFormatter& obj)
  {
    return os << obj.Capitalize();
  }
};
}