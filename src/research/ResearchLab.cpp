#include "ResearchLab.h"

#include <algorithm>
#include <cassert>
#include <ostream>

void ResearchLab::tick() {
    if(m_queue.empty()) return;

    if(m_queue[0]->tick()) {
        m_queue[0]->complete();
        for(size_t i = 0; i < m_queue.size()-1; i++) {
            m_queue[i] = m_queue[i+1];
        }
        m_queue.pop_back();
    }
}

void ResearchLab::enqueue(ResearchItem* item) {
    assert(item);
    m_queue.push_back(item);
}
bool ResearchLab::cancel(ResearchItem* item) {
    assert(item);

    size_t k = std::find(m_queue.begin(), m_queue.end(), item) - m_queue.begin();
    if(k >= m_queue.size()) return false;

    m_queue[k]->cancel();
    for(size_t i = k; i < m_queue.size()-1; i++) {
        m_queue[i] = m_queue[i+1];
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const ResearchLab& lab) {
    out << "ResearchLab";
    for(const auto& item : lab.m_queue) {
        out << "\n- " << item->toString();
    }
    return out;
}