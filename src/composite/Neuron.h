#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Neuron;

// CRTP - Curiously Recurring Template Pattern
template <typename Derived>
struct SomeNeurons
{
  template<typename T>
  void ConnectTo(T& other)
  {
    for (Neuron& from : *static_cast<Derived*>(this))
    {
      for (Neuron& to : other)
      {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};

struct Neuron : SomeNeurons<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id = 0;

  Neuron()
  {
    static unsigned int id_seq = 0;
    id = id_seq++;
  }

  Neuron* begin() { return this; }
  Neuron* end() { return this+1; }

  friend ostream& operator<<(ostream& os, const Neuron& obj)
  {
    for (Neuron* n : obj.in)
    {
      os << n->id << "\t-->\t[" << obj.id << "]" << endl;
    }
    for (Neuron* n : obj.out)
    {
      os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
  }
};

struct NeuronLayer : SomeNeurons<NeuronLayer>
{
  vector<Neuron> neurons;
  NeuronLayer(unsigned int n)
  {
    while (n-- > 0)
    {
      neurons.emplace_back(Neuron{});
    }
  }

  vector<Neuron>::iterator begin() { return neurons.begin(); }
  vector<Neuron>::iterator end() { return neurons.end(); }

  friend ostream& operator<<(ostream& os, const NeuronLayer& obj)
  {
    for (auto& n : obj.neurons) os << n;
    return os;
  }
};
