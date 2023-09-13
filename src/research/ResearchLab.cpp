#include "ResearchLab.h"

#include <algorithm>
#include <cassert>
#include <ostream>
#include <xmemory>

void ResearchLab::update(uint32_t dt) {
    if (m_queue.empty()) return;
    m_queue.front()->update(dt);
    if (m_queue.front()->isComplete()) {
        m_queue.front()->complete();
        m_queue.pop_front();
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
    task->cancel();
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