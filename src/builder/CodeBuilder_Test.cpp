#include "CodeBuilder.h"

#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

using namespace std;

vector<string> Serialize(const CodeBuilder& builder)
{
  stringstream ss;
  ss << builder << endl;

  vector<string> lines;

  for (string line; getline(ss, line); )
  {
    lines.emplace_back(move(line));
  }
  return lines;
}

TEST(CodeBuilder_Test, Test1)
{
  CodeBuilder builder("Person");

  builder.AddField("name", "string")
         .AddField("age", "int");

  auto lines = Serialize(builder);

  EXPECT_EQ("class Person", lines[0]);
  EXPECT_EQ("{", lines[1]);
  EXPECT_EQ("  string name;", lines[2]);
  EXPECT_EQ("  int age;", lines[3]);
  EXPECT_EQ("};", lines[4]);
  EXPECT_EQ(5, lines.size());
}