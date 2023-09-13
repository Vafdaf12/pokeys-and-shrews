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
        assert(amt >= 0);
        m_balance += amt;
    }

    /**
     * Withdraw money from the bank
     * @param amt The amount to withdraw
     */
    void withdraw(int amt) {
        assert(amt >= 0);
        m_balance -= amt;
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
    int m_balance;
};