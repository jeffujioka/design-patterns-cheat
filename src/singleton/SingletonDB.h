#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
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
      int popu = stoi(popu_str);
      populations_[cap_str] = popu;
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