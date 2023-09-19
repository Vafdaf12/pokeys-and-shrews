#pragma once

#include <cassert>
#include <ostream>

#include "TileEntity.h"
#include "core/Engine.h"

class Bank : public TileEntity {
public:
    inline Bank(int balance, Engine* engine = nullptr)
        : TileEntity(engine), m_balance(balance) {}

    inline int getBalance() const { return m_balance; }

    /// Deposits the given amount into the bank
    void deposit(int amt);

    /// Withdraws the given amount from the bank
    void withdraw(int amt);

    ///@return Whether there are sufficient funds for a withdrawl
    bool sufficientFunds(int amt) const;

    void interact(Hero& hero) override;

    friend inline std::ostream& operator<<(std::ostream& out, const Bank& b) {
        return (out << "Bank(" << b.m_balance << ")");
    }

private:
    int m_balance;
};