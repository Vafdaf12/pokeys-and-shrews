#include "SmartContractDemo.h"
#include "contract/SmartContract.h"

#include "util/out.h"
#include "util/util.h"

#include <exception>
#include <iostream>
#include <utility>
#include <vector>

void SmartContractDemo::init() {
    std::cout << out::clear_screen << out::home;
    std::cout.flush();

    std::string name;
    std::cout << "Contract Name: ";
    std::getline(std::cin, name);

    int count = util::input("Number of parties: ");
    std::cout << count << std::endl;

    m_pContract = new SmartContract(name, count);
}
void SmartContractDemo::execute() {
    static const std::vector<std::string> OPERATIONS = {"Add Condition",
        "Remove Condition",
        "Vote to Accept",
        "Vote to Complete",
        "Vote to Reject Contract"};

    int opt = -1;
    std::string lastError = "";
    do {
        std::cout << out::clear_screen << out::home;
        std::cout << m_pContract->toString() << std::endl;
        std::cout << "-------------------------------------" << std::endl;

        if (!lastError.empty()) {
            std::cout << out::error(lastError) << std::endl;
        }
        lastError.clear();

        std::cout.flush();
        opt = util::input(
            util::options("Choose operation (-1 to quit): ", OPERATIONS));

        try {
            switch (opt) {
            case 0: addCondition(); break;
            case 1: removeCondition(); break;
            case 2: accept(); break;
            case 3: complete(); break;
            case 4: reject(); break;
            }
        } catch (const std::exception& e) {
            lastError = e.what();
        }

    } while (opt != -1);
}
void SmartContractDemo::cleanup() {
    delete std::exchange(m_pContract, nullptr);
}

SmartContractDemo::~SmartContractDemo() {
    if (m_pContract) delete m_pContract;
}

void SmartContractDemo::addCondition() {
    std::string cond;
    std::cout << "What's the condition? ";
    std::getline(std::cin, cond);

    m_pContract->addCondition(cond);
}
void SmartContractDemo::removeCondition() {
    std::string cond;
    std::cout << "Begone! ";
    std::getline(std::cin, cond);

    m_pContract->removeCondition(cond);
}

void SmartContractDemo::accept() {
    int id = util::input("Who's accepting? ");
    m_pContract->voteAccept(id);
}
void SmartContractDemo::reject() {
    int id = util::input("Who's rejecting? ");
    m_pContract->voteReject(id);
}
void SmartContractDemo::complete() {
    int id = util::input("Who's completing? ");
    m_pContract->voteComplete(id);
}
