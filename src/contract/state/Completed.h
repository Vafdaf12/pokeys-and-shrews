#pragma once

#include "contract/ContractState.h"

class Completed : public ContractState {
public:
  Completed() : ContractState(nullptr) {}

  void addCondition(const std::string &cond) override;
  bool removeCondition(const std::string &cond) override;

  void voteAccept(int id) override;
  void voteReject(int id) override;
  void voteComplete(int id) override;

  std::string toString() const override;
};
