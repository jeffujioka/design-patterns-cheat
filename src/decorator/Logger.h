#pragma once

#include <functional>
#include <string>
#include <sstream>

using namespace std;

namespace decorator
{
struct Logger
{
  function<string()> func;
  string name;

  Logger(const function<string()> &func, const string &name)
      : func(func), name(name) {}

  string operator()() const
  {
    ostringstream oss;
    oss << "Entering func " << name << endl;
    oss << func();
    oss << "Exiting func " << name << endl;
    return oss.str();
  }
};

template<typename Func>
struct TemplatedLogger
{
  Func func;
  string name;

  TemplatedLogger(const Func& func, const string &name)
      : func(func), name(name) {}

  string operator()() const
  {
    ostringstream oss;
    oss << "Entering func " << name << endl;
    oss << func();
    oss << "Exiting func " << name << endl;
    return oss.str();
  }
};

template<typename Func>
auto make_templatedlogger(const Func& func, const string& name)
{
  return TemplatedLogger<Func>{func, name};
}

template<typename> struct VariadicLogger;

template<typename R, typename... Args>
struct VariadicLogger<R(Args...)>
{
  function<R(Args...)> func;
  string name;

  VariadicLogger(const function<R(Args...)> &func, const string &name)
      : func(func), name(name) {}

  R operator()(Args... args) const
  {
    LogEnter();
    R ret = func(args...);
    LogExit();
    return ret;
  }

  string LogEnter() const { return "Entering func "s + name + "\n"s;}
  string LogExit()  const { return "Exiting func "s  + name + "\n"s;}
};

template <typename R, typename... Args>
auto MakeVariadicLogger(R(*func)(Args...), const string& name)
{
  return VariadicLogger<R(Args...)>(function<R(Args...)>(func), name);
}

}
