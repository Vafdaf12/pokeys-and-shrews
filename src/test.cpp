#include "test.h"

#include <iostream>
#include <vcruntime.h>

#include "bank/Bank.h"
#include "core/Engine.h"
#include "research/ResearchLab.h"

namespace test {
void research_lab() {
    // Initialize Lab
    ResearchLab lab;
    lab.enqueue(new ResearchTask("Item1", 10, 10));
    lab.enqueue(new ResearchTask("Item2", 2, 10));
    lab.enqueue(new ResearchTask("Item3", 5, 10));

    // Lab ticking
    lab.update(4);
    std::cout << lab << std::endl;

    // Research completion
    lab.update(6);
    std::cout << lab << std::endl;

    // Research cancellation
    std::cout << lab << std::endl;
}
void research_engine() {
    ResearchLab* lab = new ResearchLab();
    Bank* bank = new Bank(25);
    Engine engine(lab, bank);

    ResearchTask* tasks[] = {new ResearchTask("Item1", 10, 10, &engine),
        new ResearchTask("Item2", 2, 10, &engine),
        new ResearchTask("Item3", 5, 10, &engine)};
    engine.researchRequested(tasks[0]);
    engine.researchRequested(tasks[1]);
    engine.researchRequested(tasks[2]);

    lab->update(12);
    lab->update(1);
    lab->cancel(tasks[1]);

    delete lab;
    delete bank;
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

    std::cout << "sufficientFunds(61) = " << bank.sufficientFunds(61)
              << std::endl;
    std::cout << "sufficientFunds(30) = " << bank.sufficientFunds(30)
              << std::endl;
    std::cout << bank << std::endl;
}
} // namespace test