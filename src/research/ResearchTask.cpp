#include "ResearchTask.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "core/Engine.h"

ResearchTask::ResearchTask(
    const std::string& trap, float time, int cost, Engine* engine)
    : m_trap(trap), m_totalTime(time), m_cost(cost), m_pEngine(engine) {
    assert(cost >= 0);
}

void ResearchTask::update(float dt) {
    if (m_active) m_currentTime += dt;
}
void ResearchTask::complete() {
    m_currentTime = m_totalTime;
    m_active = false;
    if (m_pEngine) m_pEngine->researchCompleted(this);
}
void ResearchTask::cancel() {
    m_active = false;
    if (m_pEngine) m_pEngine->researchCancelled(this);
}

std::ostream& operator<<(std::ostream& out, const ResearchTask& item) {
    out << item.m_trap << "(" << item.m_currentTime << "," << item.m_totalTime
        << ")";
    return out;
}