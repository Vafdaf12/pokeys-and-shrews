#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SmartContract.h"

class ContractState {
public:
    virtual ~ContractState() {}

    virtual void addCondition(const std::string& cond) = 0;
    virtual bool removeCondition(const std::string& cond) = 0;

    virtual void voteAccept(int id) = 0;
    virtual void voteReject(int id) = 0;
    virtual void voteComplete(int id) = 0;

    virtual std::string toString() const = 0;

protected:
    inline ContractState(SmartContract* pContract) : m_pContract(pContract) {}

    inline std::vector<std::string>& getConditions() const {
        return m_pContract->m_conditions;
    }
    inline std::vector<VoteState>& getVotes() const {
        return m_pContract->m_votes;
    }
    inline void setState(ContractState* pState) const {
        m_pContract->setState(pState);
    }

    SmartContract* m_pContract;
};
