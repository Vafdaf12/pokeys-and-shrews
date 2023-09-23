#pragma once

#include <cassert>
#include <ostream>
#include <valarray>

#include "TileEntity.h"
#include "core/Engine.h"
#include "graphics/BankGraphic.h"

class Bank : public TileEntity {
public:
    inline Bank(int balance, Engine* engine = nullptr)
        : TileEntity(engine), m_balance(balance) {}

    inline int getBalance() const { return m_balance; }

    inline TileEntity* clone() const override {
        return new Bank(m_balance, m_pEngine);
    }

    /// Deposits the given amount into the bank
    void deposit(int amt);

    /// Withdraws the given amount from the bank
    void withdraw(int amt);

    inline void setBalance(int b) { m_balance = b; }

    ///@return Whether there are sufficient funds for a withdrawl
    bool sufficientFunds(int amt) const;

    void interact(Hero& hero) override;

    inline Graphic* createGraphic() const override {
        return new BankGraphic(this);
    }

    friend inline std::ostream& operator<<(std::ostream& out, const Bank& b) {
        return (out << "Bank(" << b.m_balance << ")");
    }

private:
    int m_balance;
};