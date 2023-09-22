#pragma once

#include "raylib.h"
#include "research/ResearchTask.h"
#include <sstream>
#include <string>

class LabelResearch : public ResearchTask {
public:
    LabelResearch(const std::string& label,
        float time,
        int cost,
        Engine* engine = nullptr)
        : ResearchTask(time, cost, engine), m_text(label) {}

    void complete() override;
    void cancel() override;
    Graphic* createGraphic() const override;

    inline std::string toString() const override {
        std::stringstream s;
        s << "LabelResearch(" << m_text << ")";
        return s.str();
    }

private:
    std::string m_text;
};