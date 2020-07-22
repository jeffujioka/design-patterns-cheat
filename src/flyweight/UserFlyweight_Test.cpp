#include "flyweight/UserFlyweight_Test.h"

#include <gtest/gtest.h>

using namespace flyweight;

TEST(UserFlyweight_Test, Test)
{
  handmade::User jeff("Jeff", "Fujioka");
  handmade::User maria("Maria", "Fujioka");

  EXPECT_EQ("Jeff"s, jeff.get_first_name());
  EXPECT_EQ("Maria"s, maria.get_first_name());
  // both last names shall point to the same address
  EXPECT_EQ(&jeff.get_last_name(), &maria.get_last_name());
}

TEST(UserFlyweight_Test, BoostFlyweightTest)
{
  boostflyweight::User jeff{"Jeff", "Fujioka"};
  boostflyweight::User maria{"Maria", "Fujioka"};

  auto is_same_name = jeff.get_first_name() == maria.get_first_name();
  EXPECT_EQ(false, is_same_name);

  is_same_name = jeff.get_last_name() == maria.get_last_name();
  EXPECT_EQ(true, is_same_name);

  auto is_same_addr = &jeff.get_first_name() == &maria.get_first_name();
  EXPECT_EQ(false, is_same_addr);

  is_same_addr = &jeff.get_last_name() == &maria.get_last_name();
  EXPECT_EQ(true, is_same_addr);
}