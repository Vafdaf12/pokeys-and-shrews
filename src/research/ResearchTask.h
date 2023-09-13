#pragma once

#include <stdint.h>
#include <string>

/**
 * Captures the idea of a some research task that requires time and money to
 * complete. A research task plays the role of a Command in the Command Pattern,
 * with the Engine (TODO) being the Receiver
 */
class ResearchTask {
public:
    ResearchTask(const std::string& trap, uint32_t time);

    /**
     * @returns Whether the research has completed
     */
    bool tick();

    /**
     * Completes the research, notifying all relevant parties
     */
    void complete();

    /**
     * Cancels the research, notifying all relevant parties
     */
    void cancel();

    friend std::ostream& operator<<(std::ostream&, const ResearchTask&);

private:
    std::string m_trap;
    uint32_t m_totalTicks;
    uint32_t m_currentTick = 0;
    bool m_active = true;
};