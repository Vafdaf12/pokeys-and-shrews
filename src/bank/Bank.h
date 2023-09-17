#pragma once

#include <cassert>
#include <ostream>

#include "core/Engine.h"

class Bank {
public:
    inline Bank(int balance) : m_balance(balance) {}

    inline int getBalance() const { return m_balance; }
    inline void setEngine(Engine* pEngine) {
        m_pEngine = pEngine;
        m_pEngine->balanceChanged(m_balance);
    }

    /**
     * Deposits money into the bank
     * @param amt The amount to deposit
     */
    inline void deposit(int amt) {
        assert(amt >= 0);
        m_balance += amt;
        if (m_pEngine) m_pEngine->balanceChanged(m_balance);
    }

    /**
     * Withdraw money from the bank
     * @param amt The amount to withdraw
     */
    void withdraw(int amt) {
        assert(amt >= 0);
        m_balance -= amt;
        if (m_pEngine) m_pEngine->balanceChanged(m_balance);
    }

    /**
     * @return Whether there are sufficient funds for a withdrawl
     */
    bool sufficientFunds(int amt) {
        assert(amt >= 0);
        return m_balance >= amt;
    }

    friend inline std::ostream& operator<<(std::ostream& out, const Bank& b) {
        return (out << "Bank(" << b.m_balance << ")");
    }

private:
    Engine* m_pEngine = nullptr;
    ;
    int m_balance;
};