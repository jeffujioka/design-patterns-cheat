#include "decorator/ShapeDecorator.h"

#include <gtest/gtest.h>

using namespace decorator;

TEST(StaticShapeDecortor_Test, ColoredShapeIntegration)
{
  Circle c{1.5f};
  Square s{5.75f};

  statical::ColoredShape<Square> red_shape("red", 5.75f);
  EXPECT_EQ("A square of side 5.75 has the color red"s, red_shape.str());

  statical::ColoredShape<Circle> black_shape{"black", 1.5f};
  EXPECT_EQ("A circle of radius 1.5 has the color black"s, black_shape.str());
}

TEST(StaticShapeDecorator_Test, CircleResize)
{
  statical::ColoredShape<Circle> red_shape("red", 2.25f);

  EXPECT_EQ(2.25f, red_shape.radius);
  red_shape.resize(2.f);
  // with static decorator, it is now possible to access the resize method
  // from Circle class
  EXPECT_EQ(4.5f, red_shape.radius);
}
