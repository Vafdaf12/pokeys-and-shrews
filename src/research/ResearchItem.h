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

    void complete();
    void cancel();

    std::string toString() const;
private:
    std::string m_trap;
    uint32_t m_totalTicks;
    uint32_t m_currentTick = 0;
    bool m_active = true;
};