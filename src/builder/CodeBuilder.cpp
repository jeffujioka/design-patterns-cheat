#include "CodeBuilder.h"

CodeBuilder::CodeBuilder(const std::string& name) : class_name_(name) {}

CodeBuilder &CodeBuilder::AddField(const std::string &name,
                                   const std::string &type) {
  attributes_.emplace_back(std::pair{name, type});
  return *this;
}

std::ostream &operator<<(std::ostream &os, const CodeBuilder &builder) {
  using std::endl;
  os << "class " << builder.class_name_ << endl;
  os << "{" << endl;
  for (const auto& [name, type] : builder.attributes_)
  {
    os << "  " << type << " " << name << ";" << endl;
  }
  os << "};";
  return os;
}
