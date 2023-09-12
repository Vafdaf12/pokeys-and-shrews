#pragma once

#include <memory>
#include <vector>

#include "ResearchItem.h"

class ResearchLab {
public:
    ~ResearchLab();

    /**
     * Updates the research lab to perform one unit of research
     */
    void tick();

    /**
     * Enqueues the passed in item to research
     * @param item The item to research
     */
    void enqueue(ResearchItem* item);

    /**
     * Cancels the item at the specified position in the queue
     * @param item The index of the item to cancel research for
     * @return The cancelled item (if any)
     */
    ResearchItem* cancel(size_t i);

    friend std::ostream& operator<<(std::ostream&, const ResearchLab&);

private:
    std::vector<ResearchItem*> m_queue;
};