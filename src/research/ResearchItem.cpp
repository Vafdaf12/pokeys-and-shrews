#include "ResearchItem.h"

#include <iostream>
#include <sstream>

ResearchItem::ResearchItem(const std::string& trap, uint32_t time)
    : m_trap(trap), m_totalTicks(time) {}

bool ResearchItem::tick() {
    if (m_active) m_currentTick++;

    return m_currentTick >= m_totalTicks;
}
void ResearchItem::complete() {
    m_currentTick = m_totalTicks;
    m_active = false;
    std::cout << m_trap << ": COMPLETE" << std::endl;
}
void ResearchItem::cancel() {
    m_active = false;
    std::cout << m_trap << ": CANCELLED" << std::endl;
}

std::string ResearchItem::toString() const {
    std::stringstream s;
    s << m_trap << ": " << m_currentTick << "/" << m_totalTicks;
    return s.str();
}