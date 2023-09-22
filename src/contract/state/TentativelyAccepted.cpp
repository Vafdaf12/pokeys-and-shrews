#include "TentativelyAccepted.h"

#include "contract/SmartContract.h"

#include "contract/state/Accepted.h"
#include "contract/state/Negotiate.h"
#include "contract/state/Rejected.h"

#include <sstream>
#include <algorithm>
#include <stdexcept>

void TentativelyAccepted::addCondition(const std::string &cond) {
    getConditions().push_back(cond);
    for(auto& vote : getVotes()) {
        vote = VoteState::Negotiate;
    }

    setState(new Negotiate(m_pContract));
    delete this;
}
bool TentativelyAccepted::removeCondition(const std::string &cond) {
    auto& conditions = getConditions();
    int i = std::find(conditions.begin(), conditions.end(), cond) - conditions.begin();
    if(i == conditions.size()) return false;

    for(int j = i; j < conditions.size()-1; j++) {
        conditions[j] = conditions[j+1];
    }
    conditions.pop_back();

    for(auto& vote : getVotes()) {
        vote = VoteState::Negotiate;
    }

    setState(new Negotiate(m_pContract));
    delete this;

    return true;
}

void TentativelyAccepted::voteAccept(int id) {
    std::vector<VoteState>& votes = getVotes();
    votes[id] = VoteState::Accept;

    for(const auto& vote : votes) {
        if(vote != VoteState::Accept) return;
    }

    setState(new Accepted(m_pContract));
    delete this;
}
void TentativelyAccepted::voteReject(int id) {
    setState(new Rejected);
    delete this;
}
void TentativelyAccepted::voteComplete(int id) {
    throw std::runtime_error("Cannot vote to complete; contract not accepted");
}

std::string TentativelyAccepted::toString() const {
    std::stringstream stream;
    stream << "State: Tentatively Accepted\n";
    stream << "Votes:";
    for(int i = 0; i < getVotes().size(); i++) {
        const auto& vote = getVotes()[i];
        stream << "\n\t " << i << " ";
        switch(vote) {
        case VoteState::Negotiate:
            stream << "Negotiate";
            break;
        case VoteState::Accept:
            stream << "Accept";
            break;
        case VoteState::Complete:
            stream << "Complete";
            break;
        }
    }
    return stream.str();
}
