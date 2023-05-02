#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

class first_last_not_of_n_substr {
  public:
  string operator()(string& s) { return rtrim(ltrim(s)); }

  private:
  const string WHITESPACE = " \n\r\t\f\v";

  string ltrim(string s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
  }

  string rtrim(string s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
  }
};

class find_if_and_erase {
  public:
  string& operator()(string& s) { return ltrim(rtrim(s)); }

  private:
  string& ltrim(string& s) {
    auto it = find_if(s.begin(), s.end(), [](char c) { return !isspace<char>(c, locale::classic()); });
    s.erase(s.begin(), it);
    return s;
  }

  string& rtrim(string& s) {
    auto it = find_if(s.rbegin(), s.rend(), [](char c) { return !isspace<char>(c, locale::classic()); });
    s.erase(it.base(), s.end());
    return s;
  }
};

class hand_written_code {
  public:
  string operator()(const string& s) { return trim(s); }

  private:
  string trim(const string& s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
      start++;
    }

    auto end = s.end();
    do {
      end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
  }
};

class cpp11_regex {
  public:
  string operator()(const string& s) { return ltrim(rtrim(s)); }

  private:
  string ltrim(const string& s) { return regex_replace(s, regex("^\\s+"), string("")); }

  string rtrim(const string& s) { return regex_replace(s, regex("\\s+$"), string("")); }
};

class using_boost {
  public:
  void operator()(string& s) { boost::algorithm::trim(s); }
};
