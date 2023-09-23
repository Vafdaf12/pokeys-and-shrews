#pragma once

#include "entity/TileEntity.h"
#include "research/ResearchTask.h"

#include <sstream>
#include <string>

class TrapResearch : public ResearchTask {
public:
    friend class TrapResearchGraphic;
    TrapResearch(
        TileEntity* entity, float time, int cost, Engine* engine = nullptr)
        : ResearchTask(time, cost, engine), m_entity(entity) {}

    void complete() override;
    void cancel() override {}
    gfx::Graphic* createGraphic() const override;

    inline std::string toString() const override {
        std::stringstream s;
        s << "TrapResearch(" << m_entity << ")";
        return s.str();
    }

private:
    TileEntity* m_entity;
};