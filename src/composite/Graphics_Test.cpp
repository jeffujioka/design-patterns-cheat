#include "composite/Graphics.h"

#include <gtest/gtest.h>

TEST(GraphicsObject_Test, GraphicsGroup)
{
  Group g("Group 1");
  // TODO replace Circle by gmock implementation to be able to use EXPECT_CALL
  Circle c1, c2;
  g.objects.push_back(&c1);
  g.objects.push_back(&c2);
  g.Draw();
}
