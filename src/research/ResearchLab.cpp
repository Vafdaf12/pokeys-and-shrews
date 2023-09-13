#include "ResearchLab.h"

#include <algorithm>
#include <cassert>
#include <ostream>
#include <xmemory>

void ResearchLab::tick() {
    if (m_queue.empty()) return;

    if (m_queue[0]->tick()) {
        m_queue[0]->complete();
        m_queue.erase(std::remove(m_queue.begin(), m_queue.end(), m_queue[0]));
    }
}

void ResearchLab::enqueue(ResearchTask* item) {
    assert(item);
    m_queue.push_back(item);
}
bool ResearchLab::cancel(ResearchTask* task) {
    assert(task);
    auto it = std::remove(m_queue.begin(), m_queue.end(), task);
    if (it == m_queue.end()) return false;

    m_queue.erase(it);
    return true;
}

std::ostream& operator<<(std::ostream& out, const ResearchLab& lab) {
    out << "ResearchLab";
    for (const auto& item : lab.m_queue) {
        out << "\n- " << *item;
    }
    return out;
}