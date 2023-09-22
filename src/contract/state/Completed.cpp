#include "Completed.h"

void Completed::addCondition(const std::string &cond) {}
bool Completed::removeCondition(const std::string &cond) { return false; }

void Completed::voteAccept(int id) {}
void Completed::voteReject(int id) {}
void Completed::voteComplete(int id) {}

std::string Completed::toString() const { return "State: Completed"; }
