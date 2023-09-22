#pragma once

#include <stdint.h>
class Timer {
public:
    Timer(float time = 0, bool completed = false) : m_time(time) {
        if (completed) m_current = time;
    }

    inline void update(float dt) { m_current += dt; }
    inline bool isComplete() const { return m_current >= m_time; }
    inline void reset() { m_current = 0; }
    inline void tick() { m_current -= m_time; }
    inline void setTime(float time) { m_time = time; }
    inline float getTime() const { return m_time; }
    inline float getProgress() const { return m_current / m_time; }

private:
    float m_time;
    float m_current = 0;
};