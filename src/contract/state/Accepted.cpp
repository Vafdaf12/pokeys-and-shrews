#include "Accepted.h"

#include "contract/SmartContract.h"
#include "contract/state/Completed.h"

#include <sstream>
#include <stdexcept>

void Accepted::addCondition(const std::string &cond) {
  throw std::runtime_error("Cannot add condition; contract already accepted");
}
bool Accepted::removeCondition(const std::string &cond) {
  throw std::runtime_error(
      "Cannot remove condition; contract already accepted");
}
void Accepted::voteAccept(int id) {
  throw std::runtime_error("Cannot accept contract; already accepted");
}
void Accepted::voteReject(int id) {
  throw std::runtime_error("Cannot reject contract; already accepted");
}
void Accepted::voteComplete(int id) {
  getVotes()[id] = VoteState::Complete;
  for (const auto &vote : getVotes()) {
    if (vote != VoteState::Complete)
      return;
  }
  setState(new Completed());
  delete this;
}

std::string Accepted::toString() const {
  std::stringstream stream;
  stream << "State: Accepted\n";
  stream << "Votes:";
  for (const auto &vote : getVotes()) {
    stream << "\n\t";
    switch (vote) {
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
