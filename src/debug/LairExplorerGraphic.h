#pragma once
#include "raylib.h"
#include "render/Drawable.h"

#include <vector>

class LairExplorer;

class LairExplorerGraphic : public gfx::Graphic {
public:
    LairExplorerGraphic(LairExplorer* explorer);

    void draw() override;
    void update(float dt) override;

    Rectangle getBoundingBox() const override;

private:
    Color m_color;
    Vector2 m_cur;
    LairExplorer* m_pExplorer;
    std::vector<Vector2> m_points;
};