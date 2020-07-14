#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <utility>

class Attributes
{
  std::string name_;
  std::string type_;

 public:
  Attributes(const std::string &name, const std::string &type);

  friend std::ostream &operator<<(std::ostream &os,
                                  const Attributes &attributes);
};

class CodeBuilder
{
  std::string class_name_;
  std::vector<Attributes> attributes_;
 public:
  CodeBuilder() = delete;
  CodeBuilder(const std::string& class_name);

  CodeBuilder& AddField(const std::string& name, const std::string& type);

  friend std::ostream &operator<<(std::ostream &os, const CodeBuilder &builder);

};