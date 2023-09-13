#include "ResearchTask.h"

#include <iostream>
#include <sstream>

ResearchTask::ResearchTask(const std::string& trap, uint32_t time)
    : m_trap(trap), m_totalTicks(time) {}

bool ResearchTask::tick() {
    if (m_active) m_currentTick++;

    return m_currentTick >= m_totalTicks;
}
void ResearchTask::complete() {
    m_currentTick = m_totalTicks;
    m_active = false;
    std::cout << m_trap << ": COMPLETE" << std::endl;
}
void ResearchTask::cancel() {
    m_active = false;
    std::cout << m_trap << ": CANCELLED" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const ResearchTask& item) {
    out << item.m_trap << "(" << item.m_currentTick << "," << item.m_totalTicks
        << ")";
    return out;
}