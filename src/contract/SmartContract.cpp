#include "SmartContract.h"
#include "ContractState.h"
#include "contract/state/Negotiate.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>

SmartContract::SmartContract(const std::string& name, int parties)
    : m_name(name), m_votes(parties, VoteState::Negotiate),
      m_pState(new Negotiate(this)) {}

void SmartContract::addCondition(const std::string& cond) {
    m_pState->addCondition(cond);
}
bool SmartContract::removeCondition(const std::string& cond) {
    return m_pState->removeCondition(cond);
}

void SmartContract::voteAccept(int id) { m_pState->voteAccept(id); }
void SmartContract::voteReject(int id) { m_pState->voteReject(id); }
void SmartContract::voteComplete(int id) { m_pState->voteComplete(id); }

std::string SmartContract::toString() const {
    std::stringstream stream;
    stream << "Contract " << m_name;

    std::stringstream stateStream(m_pState->toString());
    std::string line;
    while (!stateStream.eof()) {
        std::getline(stateStream, line);
        stream << "\n\t" << line;
    }

    stream << "\n\tConditions:";
    for (const auto& cond : m_conditions) {
        stream << "\n\t\t" << cond;
    }

    return stream.str();
}
