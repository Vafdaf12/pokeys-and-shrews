#include "Bank.h"

#include "hero/Hero.h"

#include <cmath>

void Bank::deposit(int amt) {
    assert(amt >= 0);
    m_balance += amt;
    if (m_pEngine) m_pEngine->balanceChanged(m_balance);
}

void Bank::withdraw(int amt) {
    assert(amt >= 0);
    m_balance -= amt;
    if (m_pEngine) m_pEngine->balanceChanged(m_balance);
}

bool Bank::sufficientFunds(int amt) const {
    assert(amt >= 0);
    return m_balance >= amt;
}

void Bank::interact(Hero& hero) {
    if (m_pEngine) m_pEngine->heroInteracted(this, &hero);
}