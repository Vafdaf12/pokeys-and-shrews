#pragma once

#include <string>
#include <vector>

class ContractState;

enum class VoteState { Negotiate, Accept, Complete };

class ContractObserver {
public:
    virtual void notify() = 0;
};

class SmartContract {
public:
    SmartContract(const std::string& name, int parties);

    ~SmartContract();

    void addCondition(const std::string& cond);
    bool removeCondition(const std::string& cond);

    void voteAccept(int id);
    void voteReject(int id);
    void voteComplete(int id);

    std::string toString() const;

    friend class ContractState;

    void subscribe(ContractObserver* obs) { m_observers.push_back(obs); }
    void unsubscribe(ContractObserver* obs) { std::erase(m_observers, obs); }

private:
    void setState(ContractState* s) {
        if (s == m_pState) return;
        m_pState = s;
        for (auto o : m_observers)
            o->notify();
    }
    std::string m_name;

    std::vector<std::string> m_conditions;
    std::vector<VoteState> m_votes;
    std::vector<ContractObserver*> m_observers;

    ContractState* m_pState;
};
