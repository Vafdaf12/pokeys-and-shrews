#include "DepthFirstExplorer.h"

DepthFirstExplorer::DepthFirstExplorer(Tile* start)
    : m_pStart(start), m_pCurrent(start) {}

void DepthFirstExplorer::setStart(Tile* tile) {
    m_explored.clear();
    while (!m_depth.empty())
        m_depth.pop();
    m_pCurrent = tile;
    m_pStart = tile;
}

void DepthFirstExplorer::backtrack(uint32_t n) {
    for (int i = 0; i < n; i++) {
        m_pCurrent = m_path.back();
        if (!m_depth.empty() && m_pCurrent == m_depth.top()) {
            m_depth.pop();
        }
        m_path.pop_back();
        m_explored.erase(m_pCurrent);
    }
}
void DepthFirstExplorer::next() {
    m_explored.insert(m_pCurrent);
    m_path.push_back(m_pCurrent);
    Tile* next = getNextNeighbor();
    // Immediate neighbour
    if (next) {
        m_depth.push(m_pCurrent);
        m_pCurrent = next;
        return;
    }
    // Done exploring
    if (m_depth.empty()) {
        m_pCurrent = m_pStart;
        m_explored.clear();
        this->next();
        return;
    }

    // Backtrack
    m_pCurrent = m_depth.top();
    m_depth.pop();
}
Tile* DepthFirstExplorer::getNextNeighbor() {
    if (!m_pCurrent) return nullptr;

    Tile* n = m_pCurrent->getNeighbour(Tile::North);
    Tile* s = m_pCurrent->getNeighbour(Tile::South);
    Tile* w = m_pCurrent->getNeighbour(Tile::West);
    Tile* e = m_pCurrent->getNeighbour(Tile::East);

    if (n && !m_explored.contains(n)) return n;
    if (s && !m_explored.contains(s)) return s;
    if (w && !m_explored.contains(w)) return w;
    if (e && !m_explored.contains(e)) return e;
    return nullptr;
}
