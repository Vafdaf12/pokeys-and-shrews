#include "ResearchLab.h"
#include "core/Engine.h"

#include <algorithm>
#include <cassert>
#include <ostream>
#include <xmemory>

void ResearchLab::update(float dt) {
    if (m_queue.empty()) return;
    m_queue.front()->update(dt);
    if (!m_queue.front()->isComplete()) return;

    if (m_pEngine) {
        m_pEngine->researchCompleted(this, m_queue.front().get());
    }
    m_queue.front()->complete();
    m_queue.pop_front();
}

void ResearchLab::enqueue(ResearchTask* item) {
    assert(item);
    m_queue.emplace_back(item);
    if (m_pEngine) {
        m_pEngine->researchRequested(this, item);
    }
}
bool ResearchLab::cancel(ResearchTask* task) {
    assert(task);
    auto it = std::find_if(m_queue.begin(),
        m_queue.end(),
        [task](const auto& p) { return p.get() == task; });

    if (it == m_queue.end()) return false;
    if (m_pEngine) {
        m_pEngine->researchCancelled(this, task);
    }
    task = it->release();
    task->cancel();
    m_queue.erase(it);
    return true;
}

std::ostream& operator<<(std::ostream& out, const ResearchLab& lab) {
    out << "ResearchLab";
    for (const auto& item : lab.m_queue) {
        out << "\n- " << item->toString();
    }
    return out;
}