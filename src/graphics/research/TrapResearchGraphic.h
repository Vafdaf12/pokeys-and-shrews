#pragma once

#include "core/Graphic.h"

class TrapResearch;

class TrapResearchGraphic : public Graphic {
public:
    TrapResearchGraphic(const TrapResearch* trap);
    void draw() override;
    Rectangle getBoundingBox() const override;

private:
    Graphic* m_graphic;
    const TrapResearch* m_research;
};