#include "decorator/ShapeDecorator.h"

#include <gtest/gtest.h>

using namespace decorator;

TEST(DynamicShapeDecorator_Test, CircleAndSquareIntegration)
{
  Circle c{1.5f};
  Square s{5.75f};

  EXPECT_EQ("A circle of radius 1.5"s, c.str());
  EXPECT_EQ("A square of side 5.75", s.str());
}

TEST(DynamicShapeDecorator_Test, ColoredShapeIntegration)
{
  Circle c{1.5f};
  Square s{5.75f};

  dynamical::ColoredShape red_shape(s, "red");
  EXPECT_EQ("A square of side 5.75 has the color red"s, red_shape.str());

  dynamical::ColoredShape black_shape{c, "black"};
  EXPECT_EQ("A circle of radius 1.5 has the color black"s, black_shape.str());
}

TEST(DynamicShapeDecorator_Test, CircleResize)
{
  Circle c(2.25);
  dynamical::ColoredShape red_shape(c, "red");

  EXPECT_EQ(2.25f, c.radius);
  c.resize(2.f);
  // not able to access the resize method from ColoredShape
  // with this Decorator type
  // red_shape.resize(2.f);
  EXPECT_EQ(4.5f, c.radius);
}

TEST(ShapeDecorator_Test, TransparentColoredIntegration_DISABLED)
{
  Square square(5.f);
  dynamical::ColoredShape yellow_shape{square, "yellow"};
  dynamical::TransparentShape transparent{yellow_shape, 51};

  EXPECT_EQ("A square of side 5 has the color yellow has 20% transparency"s,
            transparent.str());
}