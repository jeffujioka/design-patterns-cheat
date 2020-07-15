#include "bridge/Person.h"
#include <iostream>
using namespace std;

struct Person::PersonImpl
{
  string name;
  PersonImpl();
  PersonImpl(const string &name) : name(name) {}

  ~PersonImpl() {}

  string GreetImpl()
  {
    string greet = "Hallö, Ich bin ";
    greet.append(name);
    greet.append("!");
    return greet;
  }
};

Person::Person(const std::string &name) : impl_(name) {}

string Person::Greet() { return impl_->GreetImpl(); }
