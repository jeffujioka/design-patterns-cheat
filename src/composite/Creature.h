#pragma once

#include <array>
#include <numeric>
#include <functional>

using namespace std;

struct Creature
{
  enum Abilities { kStrength, kAgility, kIntelligence, kCount};
  array<int, kCount> abilities;

  int strength() const { return abilities[kStrength]; }
  void set_strength(int new_value) { abilities[kStrength] = new_value; }

  int intelligence() const { return abilities[kIntelligence]; }
  void set_intelligence(int new_value) { abilities[kIntelligence] = new_value; }

  int agility() const { return abilities[kAgility]; }
  void set_agility(int new_value) { abilities[kAgility] = new_value; }

  int Sum() const
  {
    int sum = 0;
    for (auto abl : abilities)
    {
      sum += abl;
    }
    return sum;
  }

  double Avg() const { return Sum() / static_cast<double>(kCount); }
};