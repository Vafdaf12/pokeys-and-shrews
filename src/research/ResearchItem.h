#pragma once

#include <stdint.h>
#include <string>

class ResearchItem {
public:
    ResearchItem(const std::string& trap, uint32_t time);

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

    friend std::ostream& operator<<(std::ostream&, const ResearchItem&);

private:
    std::string m_trap;
    uint32_t m_totalTicks;
    uint32_t m_currentTick = 0;
    bool m_active = true;
};