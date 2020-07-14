#include "BankAccount.h"

#include <gtest/gtest.h>

TEST(BankAccount, Integration)
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

TEST(BankAccount, IntegrationUndo)
{
  BankAccount ba("Jeff");
  CompositeBankAccount commands{
    BankAccountCommand{ba, BankAccountCommand::kDeposit, 200},
    BankAccountCommand{ba, BankAccountCommand::kWithdraw, 100},
    BankAccountCommand{ba, BankAccountCommand::kWithdraw, 100},
    BankAccountCommand{ba, BankAccountCommand::kDeposit, 100},
    BankAccountCommand{ba, BankAccountCommand::kWithdraw, 1000}};

  commands.Call();
  EXPECT_EQ(100.0, ba.balance());
  commands.Undo();
  EXPECT_EQ(0, ba.balance());
}

TEST(BankAccount, IntegrationTransfer)
{
  BankAccount b1("Jeff");
  BankAccount b2("Maria");
  b1.Deposit(550);

  MoneyTransferCommand transfer{b1, b2, 100};

  transfer.Call();
  EXPECT_EQ(450.0, b1.balance());
  EXPECT_EQ(100.0, b2.balance());

  transfer.Undo();
  EXPECT_EQ(550.0, b1.balance());
  EXPECT_EQ(0.0, b2.balance());
}
TEST(BankAccount, IntegrationInvalidTransfer)
{
  BankAccount b1("Jeff");
  BankAccount b2("Maria");
  b1.Deposit(100);

  MoneyTransferCommand transfer{b1, b2, 1000};

  transfer.Call();
  EXPECT_EQ(100.0, b1.balance());
  EXPECT_EQ(0.0, b2.balance());

  transfer.Undo();
  EXPECT_EQ(100.0, b1.balance());
  EXPECT_EQ(0.0, b2.balance());
}
