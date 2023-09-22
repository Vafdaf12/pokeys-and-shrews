#pragma once

#include "core/Graphic.h"

class TrapResearch;

class TrapResearchGraphic : public Graphic {

    TrapResearchGraphic(const TrapResearch* trap);
    void draw() override;
    Rectangle getBoundingBox() const override;

private:
    Graphic* m_graphic;
    TrapResearch* m_research;
};