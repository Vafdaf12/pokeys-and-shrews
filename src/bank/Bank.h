#pragma once

#include <cassert>
#include <ostream>

class Bank {
public:
    inline Bank(int balance) : m_balance(balance) {}

    inline int getBalance() const { return m_balance; }

    /**
     * Deposits money into the bank
     * @param amt The amount to deposit
     */
    inline void deposit(int amt) {
        assert(amt > 0);
        m_balance += amt;
    }

    /**
     * Withdraw money from the bank given enough funds
     * @param amt The amount to withdraw
     * @return Whether the withdrawl was successful
     */
    bool withdraw(int amt) {
        assert(amt > 0);
        if (m_balance < amt) return false;
        m_balance -= amt;
        return true;
    }

    friend inline std::ostream& operator<<(std::ostream& out, const Bank& b) {
        return (out << "Bank(" << b.m_balance << ")");
    }

private:
    int m_balance;
};