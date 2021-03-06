#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class BankAccount
{
  std::string name_;
  double balance_ = 0.0;
  double overdraft_limit = -500.0;

 public:
  BankAccount(const std::string &name) : name_(name) {}
  BankAccount() = delete;

  double balance() const { return balance_; }

  void Deposit(double amount)
  {
    balance_ += amount;
    using namespace std;
    cout << fixed << setprecision(2) << setw(2);
    cout << " @" << name_ << ": Deposit €" << amount << ", balance now €"
         << balance_ << endl;
  }

  bool Withdraw(double amount)
  {
    using namespace std;
    if (balance_ - amount >= overdraft_limit)
    {
      balance_ -= amount;
      cout << " @" << name_ << ": Withdraw €" << amount << ", balance now €"
           << balance_ << endl;
      return true;
    }
    cout << " @" << name_ << ": FAILED! Withdraw €" << amount
         << ", balance now €" << balance_ << endl;
    return false;
  }
};

class Command
{
 protected:
  bool succeeded_;
 public:
  virtual ~Command() = default;
  bool succeeded() const { return succeeded_; }
  virtual void Call() = 0;
  virtual void Undo() = 0;
};

class BankAccountCommand : public Command
{
 public:
  enum Action {kDeposit, kWithdraw};

 private:
  BankAccount& account_;
  Action action_;
  double amount_;

 public:
  BankAccountCommand(BankAccount &account, Action action, double amount)
      : account_(account), action_(action), amount_(amount) {}

  void Call() override
  {
    switch (action_) {
      case kDeposit:
        account_.Deposit(amount_);
        succeeded_ = true;
        break;

      case kWithdraw:
        if (account_.Withdraw(amount_)) succeeded_ = true;
        else succeeded_ = false;
        break;

      default: break;
    }
  }

  void Undo() override
  {
    switch (action_) {
      case kDeposit:
        account_.Withdraw(amount_);
        break;
      case kWithdraw:
        if (succeeded_) account_.Deposit(amount_);
        break;
    }
  }
};

class CompositeBankAccount : public Command
{
 protected:
  std::vector<BankAccountCommand> commands_;

 public:
  CompositeBankAccount(std::initializer_list<BankAccountCommand> il)
    : commands_(il) {}

  void Call() override
  {
    using namespace std;
    cout << "Calling " << commands_.size() << " commands" << endl;
    for (auto& cmd : commands_)
    {
      cmd.Call();
    }
  }

  void Undo() override
  {
    using namespace std;
    cout << "Undoing " << commands_.size() << " commands" << endl;
    for (auto it = commands_.rbegin(); it != commands_.rend(); ++it)
    {
      it->Undo();
    }
  }
};

class DependentBankAccount : public CompositeBankAccount
{
 public:
  DependentBankAccount(const std::initializer_list<BankAccountCommand> &items)
      : CompositeBankAccount(items) {}

  void Call() override
  {
    bool success = true;
    for (auto& cmd : commands_)
    {
      if (success)
      {
        cmd.Call();
        success = cmd.succeeded();
      }
      else
      {
        success = false;
      }
    }
  }
};

class MoneyTransferCommand : public DependentBankAccount
{
 public:
  MoneyTransferCommand(BankAccount &from,
                       BankAccount &to,
                       double amount)
      : DependentBankAccount{
      BankAccountCommand{from, BankAccountCommand::kWithdraw, amount},
      BankAccountCommand{to, BankAccountCommand::kDeposit, amount}} {}
};