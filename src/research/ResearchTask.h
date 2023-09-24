#pragma once

#include "core/GameObject.h"
#include "core/Timer.h"
#include <stdint.h>
#include <string>

class Engine;

/**
 * Captures the idea of a some research task that requires time and money to
 * complete. A research task plays the role of a Command in the Command Pattern,
 * with the Engine (TODO) being the Receiver
 */
class ResearchTask : public GameObject {
public:
    inline ResearchTask(float time, int cost, Engine* engine = nullptr)
        : GameObject(engine), m_timer(time), m_cost(cost) {}

    inline int getCost() const { return m_cost; }
    inline bool isComplete() const { return m_timer.isComplete(); }
    inline float getProgress() const { return m_timer.getProgress(); }
    inline void reset() { m_timer.reset(); }

    /**
     * Updates the research task
     * @param dt The time that has passed since the last update
     */
    void update(float dt);

    virtual void complete() = 0;
    virtual void cancel() = 0;

    virtual std::string toString() const { return "ResearchTask(\?\?\?)"; }

private:
    Timer m_timer;
    int m_cost;
};