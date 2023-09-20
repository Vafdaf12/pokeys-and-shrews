
#pragma once

#include "lair/LairExplorer.h"

#include <list>
#include <queue>
#include <set>

class BreadthFirstExplorer : public LairExplorer {
public:
    BreadthFirstExplorer(Tile* start);

    void setStart(Tile* tile) override;

    void backtrack(uint32_t n = 1) override;
    void next() override;

    inline Tile* get() const override { return m_pCurrent; }
    inline Tile* getStart() const override { return m_pStart; }

private:
    void enqueueNeighbours(Tile* tile);

    Tile* m_pStart;
    Tile* m_pCurrent;

    std::set<Tile*> m_explored;
    std::queue<Tile*> m_queue;
    std::list<Tile*> m_path;
};