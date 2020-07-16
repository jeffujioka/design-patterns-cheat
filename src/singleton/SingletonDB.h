#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;

class Database
{
 public:
  virtual int population(const string& name) = 0;
};

class SingletonDB : public Database
{
  unordered_map<string, int> populations_;

  SingletonDB()
  {
    // this file could be configurable instead of hardcoded
    ifstream ifs("capitals.txt");

    string cap_str, popu_str;

    while(getline(ifs, cap_str))
    {
      getline(ifs, popu_str);
      populations_[cap_str] = boost::lexical_cast<int>(popu_str);;
    }
  }

 public:
  static SingletonDB& GetInstance()
  {
    static SingletonDB instance;
    return instance;
  }

  SingletonDB(const SingletonDB&) = delete;
  SingletonDB& operator=(const SingletonDB&) = delete;

  ~SingletonDB() = default;

  int population(const string& name) override
  {
    return populations_[name];
  }
};

struct RecordFinder
{
  Database& db;
  RecordFinder(Database &db) : db(db) {}

  int population(const string& name) { return db.population(name); }

  int total_population(vector<string>& capitals)
  {
    int total = 0;
    for (auto& name : capitals) total += db.population(name);
    return total;
  }
};