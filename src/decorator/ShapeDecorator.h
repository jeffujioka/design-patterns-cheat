#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace decorator {

struct Shape {
  virtual string str() const = 0;
};

struct Circle : Shape {
  float radius;

  Circle(float radius) : radius(radius) {}

  string str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }

  void resize(float factor) { radius *= factor; }
};

struct Square : Shape {
  float side;

  Square(float side) : side(side) {}

  string str() const override {
    ostringstream oss;
    oss << "A square of side " << side;
    return oss.str();
  }
};

namespace dynamical {

struct ColoredShape : Shape {
  Shape &shape;
  string color;

  ColoredShape(Shape &shape, string color) : shape(shape), color(color) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

struct TransparentShape : Shape {
  Shape &shape;
  uint8_t transparency;

  TransparentShape(Shape &shape, uint8_t transparency)
      : shape(shape), transparency(transparency) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";
    return oss.str();
  }
};

}

}