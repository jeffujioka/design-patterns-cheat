#pragma once

#include "string"

#include "bridge/Pimpl.h"

struct Person {
  struct PersonImpl;
  Pimpl<PersonImpl> impl_;

 public:
  Person(const std::string &name);

  Person() = delete;

  std::string Greet();
};
