#pragma once

#include <vector>

#include "ResearchItem.h"

class ResearchLab {
public:
    void tick();

    void enqueue(ResearchItem* item);
    bool cancel(ResearchItem* item);

    friend std::ostream& operator<<(std::ostream&, const ResearchLab&);
private:
    void remove(int i);
    std::vector<ResearchItem*> m_queue;
};