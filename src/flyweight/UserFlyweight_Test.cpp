#include "flyweight/UserFlyweight_Test.h"

#include <gtest/gtest.h>

using namespace flyweight;

TEST(UserHandMadeFlyweight_Test, Test)
{
  handmade::User jeff("Jeff", "Fujioka");
  handmade::User maria("Maria", "Fujioka");

  EXPECT_EQ("Jeff"s, jeff.get_first_name());
  EXPECT_EQ("Maria"s, maria.get_first_name());
  // both last names shall point to the same address
  EXPECT_EQ(&jeff.get_last_name(), &maria.get_last_name());
}
