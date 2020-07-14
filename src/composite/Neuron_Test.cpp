#include "composite/Neuron.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(Neuron_Test, ConnectTo)
{
  Neuron n1, n2;

  n1.ConnectTo(n2);
  // TODO add EXPECT_EQs
}
TEST(Neuron_Test, ConnectToLayer)
{
  Neuron n1, n2;

  n1.ConnectTo(n2);
  NeuronLayer l1{5};
  l1.ConnectTo(n1);
  // TODO add EXPECT_EQs
}
