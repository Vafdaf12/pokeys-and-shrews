#include "test.h"

#include <iostream>
#include <vcruntime.h>

#include "bank/Bank.h"
#include "research/ResearchLab.h"

namespace test {
void research_lab() {
    // Initialize Lab
    ResearchLab lab;
    lab.enqueue(new ResearchItem("Item1", 10));
    lab.enqueue(new ResearchItem("Item2", 2));
    lab.enqueue(new ResearchItem("Item3", 5));

    // Lab ticking
    for (int i = 0; i < 4; i++) {
        lab.tick();
    }
    std::cout << lab << std::endl;

    // Research completion
    for (int i = 0; i < 6; i++) {
        lab.tick();
    }
    std::cout << lab << std::endl;

    // Research cancellation
    delete lab.cancel(1);
    std::cout << lab << std::endl;
}
void bank() {
    Bank bank(100);
    std::cout << bank << std::endl;

    // Deposit
    bank.deposit(10);
    std::cout << "deposit(10) => " << bank << std::endl;

    // Withdraw
    bank.withdraw(50);
    std::cout << "withdraw(55) => " << bank << std::endl;

    std::cout << "withdraw(61) = " << bank.withdraw(61) << std::endl;
    std::cout << "withdraw(30) = " << bank.withdraw(30) << std::endl;
    std::cout << bank << std::endl;
}
} // namespace test