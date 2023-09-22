#pragma once

#include <string>
#include <vector>

class ContractState;

enum class VoteState { Negotiate, Accept, Complete };

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

private:
    std::string m_name;

    std::vector<std::string> m_conditions;
    std::vector<VoteState> m_votes;

    ContractState* m_pState;
};
