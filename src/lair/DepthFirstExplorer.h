#pragma once

#include "lair/LairExplorer.h"

#include <list>
#include <set>
#include <stack>


class DepthFirstExplorer : public LairExplorer {
public:
    DepthFirstExplorer(Tile* start);

    void setStart(Tile* tile) override;

    void backtrack(uint32_t n = 1) override;
    void next() override;

    inline Tile* get() const override { return m_pCurrent; }
    inline Tile* getStart() const override { return m_pStart; }

private:
    Tile* getNextNeighbor();

    Tile* m_pStart;
    Tile* m_pCurrent;
    std::set<Tile*> m_explored;
    std::stack<Tile*> m_depth;
    std::list<Tile*> m_path;
};