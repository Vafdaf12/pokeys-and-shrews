#pragma once

#include <list>

#include "ResearchTask.h"

/**
 * Manages the completion of research tasks submitted to it, but does not manage
 * any memory pertaining to a research task
 */
class ResearchLab {
public:
    /**
     * Updates the research lab to perform one unit of research
     */
    void update(float dt);

    /**
     * Enqueues the passed in item to research
     * @param item The item to research
     */
    void enqueue(ResearchTask* item);

    /**
     * Cancels the passed in research task (if it is queued)
     * @param task The task to cancel
     * @return Whether the task was cancelled
     */
    bool cancel(ResearchTask* task);

    friend std::ostream& operator<<(std::ostream&, const ResearchLab&);

private:
    std::list<ResearchTask*> m_queue;
};