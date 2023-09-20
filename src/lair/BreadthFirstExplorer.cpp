#include "BreadthFirstExplorer.h"

BreadthFirstExplorer::BreadthFirstExplorer(Tile* start)
    : m_pStart(start), m_pCurrent(start) {}

void BreadthFirstExplorer::setStart(Tile* tile) {
    m_explored.clear();
    m_path.clear();
    while (!m_queue.empty())
        m_queue.pop();
    m_pCurrent = tile;
    m_pStart = tile;
}

void BreadthFirstExplorer::backtrack(uint32_t n) {
    for (int i = 0; i < n; i++) {
        if (m_path.empty()) break;
        m_pCurrent = m_path.back();
        m_path.pop_back();
        m_explored.erase(m_pCurrent);
    }
}
void BreadthFirstExplorer::next() {
    m_explored.insert(m_pCurrent);
    m_path.push_back(m_pCurrent);
    enqueueNeighbours(m_pCurrent);
    if (!m_queue.empty()) {
        m_pCurrent = m_queue.front();
        m_queue.pop();

    } else {
        m_explored.clear();
    }
}
void BreadthFirstExplorer::enqueueNeighbours(Tile* tile) {
    if (!tile) return;

    Tile* n = m_pCurrent->getNeighbour(Tile::North);
    Tile* s = m_pCurrent->getNeighbour(Tile::South);
    Tile* w = m_pCurrent->getNeighbour(Tile::West);
    Tile* e = m_pCurrent->getNeighbour(Tile::East);

    if (n && !m_explored.contains(n)) {
        m_queue.push(n);
        m_explored.insert(n);
    }
    if (e && !m_explored.contains(e)) {
        m_queue.push(e);
        m_explored.insert(e);
    }
    if (s && !m_explored.contains(s)) {
        m_queue.push(s);
        m_explored.insert(s);
    }
    if (w && !m_explored.contains(w)) {
        m_queue.push(w);
        m_explored.insert(w);
    }
}
