#include "Negotiate.h"

#include "contract/SmartContract.h"

#include "contract/state/Rejected.h"
#include "contract/state/TentativelyAccepted.h"

#include <algorithm>
#include <stdexcept>

void Negotiate::addCondition(const std::string &cond) {
    getConditions().push_back(cond);
}
bool Negotiate::removeCondition(const std::string &cond) {
    auto& conditions = getConditions();
    int i = std::find(conditions.begin(), conditions.end(), cond) - conditions.begin();
    if(i == conditions.size()) return false;

    for(int j = i; j < conditions.size()-1; j++) {
        conditions[j] = conditions[j+1];
    }
    conditions.pop_back();
    return true;
}

void Negotiate::voteAccept(int id) {
    getVotes()[id] = VoteState::Accept;

    setState(new TentativelyAccepted(m_pContract));
    delete this;
}
void Negotiate::voteReject(int id) {
    setState(new Rejected);
    delete this;
}
void Negotiate::voteComplete(int id) {
    throw std::runtime_error("Cannot vote to complete; contract not accepted");
}

std::string Negotiate::toString() const {
    return "State: Negotiate";
}
