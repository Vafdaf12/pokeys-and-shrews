#pragma once

#include "Task.h"
#include "contract/SmartContract.h"

#include <memory>
#include <vector>


class SmartContract;

class SmartContractDemo : public Task {
public:
    ~SmartContractDemo();

private:
    void init() override;
    void execute() override;
    void cleanup() override;

    void addCondition();
    void removeCondition();

    void accept();
    void reject();
    void complete();

private:
    SmartContract* m_pContract = nullptr;
    std::vector<std::unique_ptr<ContractObserver>> m_observers;
};
