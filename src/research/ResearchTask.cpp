#include "ResearchTask.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "core/Engine.h"

ResearchTask::ResearchTask(
    const std::string& trap, uint32_t time, int cost, Engine* engine)
    : m_trap(trap), m_totalTicks(time), m_cost(cost), m_pEngine(engine) {
    assert(cost >= 0);
}

void ResearchTask::update(uint32_t dt) {
    if (m_active) m_currentTick += dt;
}
void ResearchTask::complete() {
    m_currentTick = m_totalTicks;
    m_active = false;
    if (m_pEngine) m_pEngine->researchCompleted(this);
}
void ResearchTask::cancel() {
    m_active = false;
    if (m_pEngine) m_pEngine->researchCancelled(this);
}

std::ostream& operator<<(std::ostream& out, const ResearchTask& item) {
    out << item.m_trap << "(" << item.m_currentTick << "," << item.m_totalTicks
        << ")";
    return out;
}