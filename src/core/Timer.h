#pragma once

#include <stdint.h>
class Timer {
public:
    Timer(uint32_t time = 0) : m_time(time) {}

    inline void update(uint32_t dt) { m_current += dt; }
    inline bool isComplete() const { return m_current >= m_time; }
    inline void reset() { m_current = 0; }
    inline void tick() { m_current -= m_time; }
    inline void setTime(uint32_t time) { m_time = time; }

private:
    uint32_t m_time;
    uint32_t m_current = 0;
};