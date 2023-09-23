#pragma once

#include "render/Drawable.h"

class TrapResearch;

class TrapResearchGraphic : public gfx::Graphic {
public:
    TrapResearchGraphic(const TrapResearch* trap);
    void draw() override;
    Rectangle getBoundingBox() const override;

private:
    gfx::Graphic* m_graphic;
    const TrapResearch* m_research;
};