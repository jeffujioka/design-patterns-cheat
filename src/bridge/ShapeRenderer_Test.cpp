#include "bridge/ShapeRenderer.h"

#include <gtest/gtest.h>

TEST(ShapeRenderer, TriangleRasterRender)
{
  RastRenderer r;
  EXPECT_EQ("Drawing triangle as pixels", Triangle(r).str());
}

TEST(ShapeRenderer, TrinagleVectorRender)
{
  VectorRenderer r;
  EXPECT_EQ("Drawing triangle as lines", Triangle(r).str());
}

TEST(ShapeRenderer, RetangleRasterRender)
{
  RastRenderer r;
  EXPECT_EQ("Drawing rectangle as pixels", Rectangle(r).str());
}

TEST(ShapeRenderer, RetangleVectorRender)
{
  VectorRenderer r;
  EXPECT_EQ("Drawing rectangle as lines", Rectangle(r).str());
}
