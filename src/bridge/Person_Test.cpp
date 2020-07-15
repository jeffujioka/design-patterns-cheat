#include "bridge/Person.h"

#include <gtest/gtest.h>

TEST(Person_Test, Greet)
{
  Person p("Jeff");

  EXPECT_EQ("Hallö, Ich bin Jeff!", p.Greet());
}
