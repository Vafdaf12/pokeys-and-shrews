
#pragma once

#include "contract/ContractState.h"

class Rejected : public ContractState {
public:
  Rejected() : ContractState(nullptr) {}

  void addCondition(const std::string &cond) override;
  bool removeCondition(const std::string &cond) override;

  void voteAccept(int id) override;
  void voteReject(int id) override;
  void voteComplete(int id) override;

  std::string toString() const override;
};
