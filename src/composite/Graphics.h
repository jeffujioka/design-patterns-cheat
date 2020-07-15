#pragma once

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct GraphicsObject
{
  virtual void Draw() = 0;
};

struct Circle : GraphicsObject
{
  void Draw() override
  {
    cout << "Drawing a circle!" << endl;
  }
};

struct Group : GraphicsObject
{
  string name;
  vector<GraphicsObject*> objects;

  Group(const string& name) : name(name) {}

  void Draw() override
  {
    cout << "Drawing group [" << name << "] with "
         << objects.size() << " objects\n";
    for (auto&& obj : objects) obj->Draw();
  }
};
