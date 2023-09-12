#include "ResearchLab.h"

#include <algorithm>
#include <cassert>
#include <ostream>
#include <xmemory>

ResearchLab::~ResearchLab() {
    for (auto ptr : m_queue) {
        delete ptr;
    }
}
void ResearchLab::tick() {
    if (m_queue.empty()) return;

    if (m_queue[0]->tick()) {
        m_queue[0]->complete();
        delete m_queue[0];
        m_queue.erase(std::remove(m_queue.begin(), m_queue.end(), m_queue[0]));
    }
}

void ResearchLab::enqueue(ResearchItem* item) {
    assert(item);
    m_queue.push_back(item);
}
ResearchItem* ResearchLab::cancel(size_t i) {
    assert(i >= 0 && i < m_queue.size());

    ResearchItem* item = m_queue[i];
    m_queue.erase(std::remove(m_queue.begin(), m_queue.end(), m_queue[i]));
    return item;
}

std::ostream& operator<<(std::ostream& out, const ResearchLab& lab) {
    out << "ResearchLab";
    for (const auto& item : lab.m_queue) {
        out << "\n- " << *item;
    }
    return out;
}