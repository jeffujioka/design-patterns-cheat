#include "CodeBuilder.h"

Attributes::Attributes(const std::string &name, const std::string &type)
    : name_(name), type_(type) {}

std::ostream &operator<<(std::ostream &os, const Attributes &obj) {
  os << obj.type_ << " " << obj.name_ << ";";
  return os;
}

CodeBuilder::CodeBuilder(const std::string& name) : class_name_(name) {}

CodeBuilder &CodeBuilder::AddField(const std::string &name,
                                   const std::string &type) {
  attributes_.emplace_back(Attributes{name, type});
  return *this;
}

std::ostream &operator<<(std::ostream &os, const CodeBuilder &builder) {
  using std::endl;
  os << "class " << builder.class_name_ << endl;
  os << "{" << endl;
  for (const auto& attr : builder.attributes_)
  {
    os << "  " << attr << endl;
  }
  os << "};";
  return os;
}

