#pragma once

#include <string>
#include <boost/signals2.hpp>
#include <sstream>

using namespace std;

namespace chain_of_resp
{

struct Query
{
  string creature_name;
  enum Action { kAttack, kDefense } action;
  int result;

  Query(const string &creature_name, Action action, int result)
      : creature_name(creature_name), action(action), result(result) {}
};

struct Game // mediator
{
  boost::signals2::signal<void(Query&)> queries;
};

class Creature
{
  Game& game_;
  string name_;
  int attack_, defense_;
 public:
  Creature(Game &game, const string &name, int attack, int defense)
      : game_(game), name_(name), attack_(attack), defense_(defense) {}

  string name() const { return name_; }

  int attack() const
  {
    Query q{name_, Query::kAttack, attack_};
    game_.queries(q);
    return q.result;
  }

  int defense() const
  {
    Query q{name_, Query::kDefense, defense_};
    game_.queries(q);
    return q.result;
  }

  string str() const
  {
    ostringstream oss;
    oss << "name: " << name_
        << ", attack: " << attack()
        << ", defense: " << defense();
    return oss.str();
  }

  friend ostream& operator<<(ostream& os, const Creature& obj)
  {
    return os << obj.str();
  }
};

class CreatureModifier
{
  Game& game_;
  Creature& creature_;
 public:
  CreatureModifier(Game &game, Creature &creature)
      : game_(game), creature_(creature) {}

  virtual ~CreatureModifier() = default;
};

class DoubleCreatureModifier : public CreatureModifier
{
  boost::signals2::connection conn_;
 public:
  DoubleCreatureModifier(Game &game,
                         Creature &creature)
      : CreatureModifier(game, creature)
  {
    conn_ = game.queries.connect([&](Query& q)
    {
      if (q.action == Query::kAttack && q.creature_name == creature.name())
      {
        q.result *= 2;
      }
    });
  }

  virtual ~DoubleCreatureModifier() { conn_.disconnect(); }
};
}
