#pragma once

#include <string>
#include <ostream>
#include <iostream>
#include <boost/bimap/bimap.hpp>

using namespace std;
using boost::bimaps::bimap;
using Key = uint32_t;

namespace flyweight
{
namespace handmade
{

class User
{
  Key first_name, last_name;
  static bimap<Key, string> users;
  static Key seed;

  static Key Add(const string& name)
  {
    auto it = users.right.find(name);

    if (it == users.right.end())
    {
      Key id = ++seed;
      users.insert(bimap<Key, string>::value_type(seed, name));
      return id;
    }
    return it->second;
  }

 public:
  User(const string& first_name, const string& last_name)
      : first_name(Add(first_name)), last_name(Add(last_name)) {}

  const string& get_first_name() const
  {
    return users.left.find(first_name)->second;
  }
  const string& get_last_name() const
  {
    return users.left.find(last_name)->second;
  }

  static void Info()
  {
    for (auto& [key, name] : users.left)
    {
      cout << "key: " << key << ", name: " << name << endl;
    }
  }

  friend ostream &operator<<(ostream &os, const User &user);
};

bimap<Key, string> User::users{};
Key User::seed = 0;

ostream &operator<<(ostream &os, const User &user) {
  os << "first_name: " << user.get_first_name()
     << " last_name: " << user.get_last_name() << endl;
  return os;
}

}
}
