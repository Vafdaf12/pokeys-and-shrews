#pragma once

#include <stdint.h>
#include <string>

class Engine;

/**
 * Captures the idea of a some research task that requires time and money to
 * complete. A research task plays the role of a Command in the Command Pattern,
 * with the Engine (TODO) being the Receiver
 */
class ResearchTask {
public:
    ResearchTask(const std::string& trap,
        uint32_t time,
        int cost,
        Engine* engine = nullptr);

    inline int getCost() const { return m_cost; }
    inline bool isComplete() const { return m_currentTick >= m_totalTicks; }
    inline const std::string& getName() const { return m_trap; }

    /**
     * Updates the research task
     * @param dt The time that has passed since the last update
     */
    void update(uint32_t dt);

    // Marks the research task as complete
    void complete();

    // Marks the research task as cancelled
    void cancel();

    friend std::ostream& operator<<(std::ostream&, const ResearchTask&);

private:
    std::string m_trap;
    uint32_t m_totalTicks;
    uint32_t m_currentTick = 0;
    int m_cost;
    bool m_active = true;

    Engine* m_pEngine;
};