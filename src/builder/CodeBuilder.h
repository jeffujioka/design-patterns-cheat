#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <utility>

class CodeBuilder
{
  std::string class_name_;
  std::vector<std::pair<std::string, std::string>> attributes_;
 public:
  CodeBuilder() = delete;
  CodeBuilder(const std::string& class_name);

  CodeBuilder& AddField(const std::string& name, const std::string& type);

  friend std::ostream &operator<<(std::ostream &os, const CodeBuilder &builder);

};