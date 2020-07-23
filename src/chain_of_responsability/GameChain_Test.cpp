#include "chain_of_responsability/GameChain.h"

#include <gtest/gtest.h>

namespace chain_of_resp
{

TEST(GameChain_Test, DoubleAttackIntegration)
{
  Game game;
  Creature godzila{game, "Godzila", 10, 10};

  EXPECT_EQ(10, godzila.attack());

  DoubleCreatureModifier dam{game, godzila};
  EXPECT_EQ(20, godzila.attack());
  {
    DoubleCreatureModifier dam2{game, godzila};
    EXPECT_EQ(40, godzila.attack());
  }
  EXPECT_EQ(20, godzila.attack());

}

}