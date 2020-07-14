#include "BankAccount.h"

#include <gtest/gtest.h>

TEST(BankAccount, IntegrationTest)
{
  BankAccount ba("Jeff");
  CompositeBankAccount commands{
    BankAccountCommand{ba, BankAccountCommand::kDeposit, 200.75},
    BankAccountCommand{ba, BankAccountCommand::kWithdraw, 500.25},
    BankAccountCommand{ba, BankAccountCommand::kDeposit, 100}};

  commands.Call();
  EXPECT_EQ(-199.50, ba.balance());
  commands.Undo();
  EXPECT_EQ(0, ba.balance());
}