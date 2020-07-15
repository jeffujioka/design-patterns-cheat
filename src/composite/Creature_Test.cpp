#include "composite/Creature.h"

#include <gtest/gtest.h>

TEST(Creature_Test, GettersAndSetters)
{
  Creature c;
  c.set_strength(10);
  c.set_agility(15);
  c.set_intelligence(20);

  EXPECT_EQ(10, c.strength());
  EXPECT_EQ(15, c.agility());
  EXPECT_EQ(20, c.intelligence());
}

TEST(Creature_Test, Sum)
{
  Creature c;
  c.set_strength(10);
  c.set_agility(15);
  c.set_intelligence(20);

  EXPECT_EQ(45, c.Sum());
}
TEST(Creature_Test, Average)
{
  Creature c;
  c.set_strength(10);
  c.set_agility(15);
  c.set_intelligence(20);

  EXPECT_EQ(15, c.Avg());
}
