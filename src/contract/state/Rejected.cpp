#include "Rejected.h"

void Rejected::addCondition(const std::string &cond) {}
bool Rejected::removeCondition(const std::string &cond) { return false; }

void Rejected::voteAccept(int id) {}
void Rejected::voteReject(int id) {}
void Rejected::voteComplete(int id) {}

std::string Rejected::toString() const { return "State: Rejected"; }
