#pragma once

#include <string>
#include <sstream>

using namespace std;

class Renderer
{
 public:
  virtual string Render() const = 0;
};

class Shape
{
  const Renderer& renderer_;
 protected:
  string name_;
 public:
  Shape(const Renderer& r) : renderer_{r} {}

  string str() const
  {
    ostringstream oss;
    oss << "Drawing " << name_ << " as " << renderer_.Render();
    return oss.str();
  }
};

class Triangle : public Shape
{
 public:
  Triangle(const Renderer& r) : Shape(r) { name_ = "triangle"; }
};

class Rectangle : public Shape
{
 public:
  Rectangle(const Renderer& r) : Shape(r) { name_ = "rectangle"; }
};

class RastRenderer : public Renderer
{
 public:
  string Render() const override
  {
    return "pixels";
  }
};

class VectorRenderer : public Renderer
{
 public:
  string Render() const override
  {
    return "lines";
  }
};